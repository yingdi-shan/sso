#include "mysql.h"
#include <iostream>

using namespace std;

string randomstring(){
	char str[11];
	for (int i=0; i<10; i++){
		str[i] = 'a' + rand()%26;
	}
	str[10] = '\0';
	return string(str);
}

void insert(Database* db){
	for (int i=0; i<100; i++){
		string username = randomstring();
		string pwd = randomstring();

		db->insert(username, pwd);
	}
}

void query(Database* db){

}
int main(){
	Database *db = new Database();

	db->init("tcp://localhost:3306", "root", "test", "user");

	// insert(db);
	query(db);

	return 0;
}
