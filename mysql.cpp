#include "mysql.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

void Database::init(const string &url, const string &username,const string &pwd,const string &table)
{
    driver = sql::mysql::get_mysql_driver_instance();

    this->url=url;
    this->username=username;
    this->pwd=pwd;
    this->table=table;
  //  printf("Begin init\n");
    for(int i=0; i<conn_limit; i++)
    {
        auto conn = driver->connect(url,username,pwd);
        auto stmt = conn->createStatement();
        string op = "use ";
        op += table;
        stmt->execute(op);
        delete stmt;
        connections.push(conn);
        //printf("hehe\n");
        //sql::PreparedStatement* p = conn->prepareStatement("select count(*) from user where username=? and pwd=?");
        //prep_query_m.insert(make_pair(conn,conn->prepareStatement(prep_query_str)));
       // printf("Hehe %x %d %d\n",p,prep_query_m.size(),connections.unsafe_size());
        prep_query_m[conn] = conn->prepareStatement(prep_query_str);
        prep_load_m[conn] = conn->prepareStatement(prep_load_str);
        prep_insert_m[conn] = conn->prepareStatement(prep_insert_str);
        prep_update_m[conn] = conn->prepareStatement(prep_update_str);
        //printf("%u\n",connections.unsafe_size());
    }

  //  printf("Finish init\n");


}


bool Database::login(const string &username,const string &pwd)
{
    auto conn = getConnection();
    auto prep_query = prep_query_m[conn];
    prep_query->setString(1, username);
    prep_query->setString(2, pwd);
    int row;
    sql::ResultSet* res;
    try
    {
        res = prep_query->executeQuery();
        res->first();
        row = res->getInt(1);
    }
    catch(...)
    {

    }
    //printf("db information:%d\n",row);
    returnConnection(conn);
    if(row> 0 )
    {
        delete res;
        return true;
    }
    else
    {
        delete res;
        return false;
    }
}

bool Database::insert(const string &username,const string &pwd)
{

    auto conn = getConnection();
    auto prep_insert = prep_insert_m[conn];

    prep_insert->setString(1, username);
    prep_insert->setString(2, pwd);
    sql::ResultSet * output;
    try
    {
        output = prep_insert->executeQuery();
    }
    catch(...)
    {
        returnConnection(conn);
        return false;
    }
    delete output;
    returnConnection(conn);


    return true;
}

bool Database::update(const string &username,const string &pwd)
{
    auto conn = getConnection();
    auto prep_update = prep_update_m[conn];

    prep_update->setString(2, username);
    prep_update->setString(1, pwd);
    sql::ResultSet * output;
    try
    {
        output = prep_update->executeQuery();
    }
    catch(...)
    {
        returnConnection(conn);
        if(output)delete output;
        return false;
    }
    returnConnection(conn);
    return true;
}

typedef pair<string,string> pss;

vector<pss> Database::load_users(int limit)
{

 //   printf("Begin to load\n");

    auto conn = getConnection();
    auto prep_load = prep_load_m[conn];
 //   printf("Get load\n");

    vector<pss> result;

    prep_load->setInt(1,limit);



    sql::ResultSet * output = prep_load->executeQuery();

    while(output->next())
    {
        result.push_back(make_pair(output->getString(1),output->getString(2)));
    }

    delete output;
    returnConnection(conn);
    return result;

}

sql::Connection *Database::getConnection()
{
    sql::Connection *conn;
    while(!connections.try_pop(conn))
    {
        //printf("%d\n",connections.unsafe_size());
        usleep(10);
    }
    return conn;
}

void Database::returnConnection(sql::Connection *conn)
{
    if(conn!=NULL && !conn->isClosed())
    connections.push(conn);
    else{
        auto conn = driver->connect(url,username,pwd);
        auto stmt = conn->createStatement();
        string op = "use ";
        op += table;
        stmt->execute(op);
        delete stmt;
        connections.push(conn);
        //printf("hehe\n");
        //sql::PreparedStatement* p = conn->prepareStatement("select count(*) from user where username=? and pwd=?");
        //prep_query_m.insert(make_pair(conn,conn->prepareStatement(prep_query_str)));
       // printf("Hehe %x %d %d\n",p,prep_query_m.size(),connections.unsafe_size());
        prep_query_m[conn] = conn->prepareStatement(prep_query_str);
        prep_load_m[conn] = conn->prepareStatement(prep_load_str);
        prep_insert_m[conn] = conn->prepareStatement(prep_insert_str);
        prep_update_m[conn] = conn->prepareStatement(prep_update_str);
    }
}
Database::~Database()
{
    sql::Connection * conn;
    while(!connections.empty())
    {
        connections.try_pop(conn);
        delete conn;
    }
}
