#ifndef MYSQL_H
#define MYSQL_H

#include <mysql_driver.h>
#include <string>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

using namespace std;

class Database{
	sql::mysql::MySQL_Driver *driver;
	sql::Connection *conn;
	sql::Statement* stmt;

	sql::PreparedStatement *prep_query;
	sql::PreparedStatement *prep_insert;
public:
	~Database();
	void init(const string &, const string &, const string &, const string &);

	void insert(const string &, const string &);
	string query(const string &);

	void batch_query();
};

#endif
