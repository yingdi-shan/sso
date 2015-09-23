#ifndef MYSQL_H
#define MYSQL_H

#include <mysql_driver.h>
#include <string>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <vector>
using namespace std;
typedef pair<string,string> pss;


class Database{
	sql::mysql::MySQL_Driver *driver;
	sql::Connection *conn;
	sql::Statement* stmt;

	sql::PreparedStatement *prep_query;
	sql::PreparedStatement *prep_load;
	sql::PreparedStatement *prep_update;
	sql::PreparedStatement *prep_insert;

	string url;
    string username;
    string pwd;
    string table;
    void update();
public:
	~Database();
	void init(const string &, const string &, const string &, const string &);
    vector<pss> load_users(int limit);
	bool insert(const string &, const string &);
	bool login(const string &,const string &);
    bool update(const string &,const string &);
	void batch_query();
};

#endif
