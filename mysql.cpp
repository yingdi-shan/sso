#include "mysql.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

void Database::init(const string &url, const string &username,const string &pwd,const string &table){
	driver = sql::mysql::get_mysql_driver_instance();
    for(int i=0;i<conn_limit;i++)
    {
        auto conn = driver->connect(url,username,pwd);
	    auto stmt = conn->createStatement();
	    string op = "use ";
	    op += table;
	    stmt->execute(op);
        
        connections.push(conn);
        
    }


	prep_query_str = "select count(*) from user where username=? and pwd=?";
	prep_load_str = "select * from user limit ?";
	prep_insert_str = "insert user(username, pwd) values(?, ?)";
	prep_update_str = "update user set pwd=? where username=?";

}


bool Database::login(const string &username,const string &pwd){
    auto conn = getConnection();
    auto prep_query = conn->prepareStatement(prep_query_str);
	prep_query->setString(1, username);
	prep_query->setString(2, pwd);
	int row;sql::ResultSet* res;
try{
	 res = prep_query->executeQuery();
	res->first();
     row = res->getInt(1);
}
catch(...){

}
    //printf("db information:%d\n",row);
	returnConnection(conn);
	if(row> 0 ){
		delete res;
		return true;
	}
	else{
        delete res;
        return false;
	}
}

bool Database::insert(const string &username,const string &pwd){

    auto conn = getConnection();
    auto prep_insert = conn->prepareStatement(prep_insert_str);
	
	prep_insert->setString(1, username);
	prep_insert->setString(2, pwd);
sql::ResultSet * output;
	try{
	 output = prep_insert->executeQuery();
}catch(...){
	returnConnection(conn);
	return false;
}
	delete output;
	returnConnection(conn);


	return true;
}

bool Database::update(const string &username,const string &pwd){
	auto conn = getConnection();
    auto prep_update = conn->prepareStatement(prep_update_str);
	
    prep_update->setString(2, username);
	prep_update->setString(1, pwd);
sql::ResultSet * output;
try{	
output = prep_update->executeQuery();
}catch(...){returnConnection(conn);if(output)delete output; return false;}
	returnConnection(conn);
	return true;
}

typedef pair<string,string> pss;

vector<pss> Database::load_users(int limit){
    auto conn = getConnection();
    auto prep_load = conn->prepareStatement(prep_load_str);
	

    vector<pss> result;

    prep_load->setInt(1,limit);

    sql::ResultSet * output = prep_load->executeQuery();

    while(output->next()){
        result.push_back(make_pair(output->getString(1),output->getString(2)));
    }

    delete output;
    returnConnection(conn);
    return result;

}

sql::Connection *Database::getConnection(){
    sql::Connection *conn;
    while(!connections.try_pop(conn)){
        usleep(10);
    }
    return conn;
}

void Database::returnConnection(sql::Connection *conn){
    	connections.push(conn);    
}
Database::~Database(){
    sql::Connection * conn;
	while(!connections.empty()){
        connections.try_pop(conn);
        delete conn;
    }
    delete stmt;
	delete conn;
}
