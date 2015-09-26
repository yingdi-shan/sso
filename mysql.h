#ifndef MYSQL_H
#define MYSQL_H

#include <mysql_driver.h>
#include <string>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <vector>
#include <queue>
#include <tbb/concurrent_queue.h>
using namespace tbb;
using namespace std;
typedef pair<string,string> pss;


class Database
{
    sql::mysql::MySQL_Driver *driver;
    const int conn_limit = 100;
    concurrent_queue<sql::Connection*> connections;
    map<sql::Connection*,sql::PreparedStatement*> prep_query_m;
    map<sql::Connection*,sql::PreparedStatement*> prep_load_m;
    map<sql::Connection*,sql::PreparedStatement*> prep_update_m;
    map<sql::Connection*,sql::PreparedStatement*> prep_insert_m;

    string username;
    string pwd;
    string table;
    string url;

    string prep_query_str = "select count(*) from user where username=? and pwd=?";
    string prep_load_str = "select * from user limit ?";
    string prep_insert_str = "insert user(username, pwd) values(?, ?)";
    string prep_update_str = "update user set pwd=? where username=?";


public:
    ~Database();
    void init(const string &, const string &, const string &, const string &);
    bool update(const string &username,const string &pwd);
    sql::Connection * getConnection();
    void returnConnection(sql::Connection *);
    vector<pss> load_users(int limit);
    bool insert(const string &, const string &);
    bool login(const string &,const string &);
    void batch_query();
};

#endif
