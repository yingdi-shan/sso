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


class Database{
	sql::mysql::MySQL_Driver *driver;
	sql::Statement* stmt;
    const int conn_limit = 100;    
    concurrent_queue<sql::Connection*> connections;
	string prep_query_str;
	string prep_load_str;
	string prep_update_str;
	string prep_insert_str;

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
