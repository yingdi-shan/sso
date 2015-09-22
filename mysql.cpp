#include "mysql.h"
#include <string>
#include <iostream>

using namespace std;

void Database::init(const string &url, const string &username,const string &pwd,const string &table){
	driver = sql::mysql::get_mysql_driver_instance();
	conn = driver->connect(url, username, pwd);
	stmt = conn->createStatement();

	string op = "use ";
	op += table;
	stmt->execute(op);

	prep_query = conn->prepareStatement("select * from user where username=?");
	prep_insert = conn->prepareStatement("insert user(username, pwd) values(?, ?)");
}

string Database::query(const string &username){
	const sql::SQLString sqlstring(username);
	prep_query->setString(1, sqlstring);
	sql::ResultSet* res = prep_query->executeQuery();

	if(res->next()){
		string pwd = res->getString("pwd");
		delete res;
		return pwd;
	}
	return "";
}

void Database::insert(const string &username,const string &pwd){
	prep_insert->setString(1, username);
	prep_insert->setString(2, pwd);

	prep_insert->executeQuery();
}

void Database::batch_query(){
}

Database::~Database(){
	delete stmt;
	delete conn;
}
