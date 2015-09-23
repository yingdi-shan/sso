#include "mysql.h"
#include <iostream>
#include "lru-cache.h"
#include "scalable-cache.h"
#include "string-key.h"
#include <thread>
#include <string>
#include <iostream>
#include <thread>
#include <memory>
#include <random>
#include <atomic>
#include <chrono>

bool login(Database *db,const string & username,const string &pwd,string &token_output);

bool update_user(Database *db,const string & username,const string &pwd,const string &new_pwd);

bool verify_token(const string &username,const string &token);

bool add_user(Database *db,const string & username,const string &pwd);

void init_user_cache(Database *db);
