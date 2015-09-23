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
#include "data_access.h"

typedef tstarling::ThreadSafeStringKey String;
typedef String::HashCompare HashCompare;
typedef tstarling::ThreadSafeLRUCache<String, string, HashCompare> Cache;

const int user_cache_size = 10000000;
const int token_cache_size = 10000000;

std::unique_ptr<Cache> token_cache = std::unique_ptr<Cache>(new Cache(user_cache_size));
std::unique_ptr<Cache> user_cache = std::unique_ptr<Cache>(new Cache(token_cache_size));

static string randomstring(){
	char str[11];
	for (int i=0; i<10; i++){
		str[i] = 'a' + rand()%26;
	}
	str[10] = '\0';
	return string(str);
}

void init_user_cache(Database *db){
    typedef pair<string,string> pss;
    vector<pss> && data = db->load_users(user_cache_size) ;
    for(auto &x: data)
        user_cache->insert(String(x.first.c_str(),x.first.size()),x.second);
    //printf("%u\n",user_cache->size());
}


bool login(Database *db,const string & username,const string &pwd,string &token_output){
    Cache::ConstAccessor ac;
    if(user_cache->find(ac,String(username.c_str(),username.size()))){
        printf("Cache found\n");
        if(pwd == *ac){
            token_output = randomstring();
            if(token_cache->find(ac,String(username.c_str(),username.size())))
                return true;
            token_cache->insert(String(username.c_str(),username.size()),token_output);
            return true;
        }
        else
        return false;
    }
    else{
        if(db->login(username,pwd)){
            token_output = randomstring();
            return true;
            token_cache->insert(String(username.c_str(),username.size()),token_output);
            return true;
        }
        else
            return false;
    }
}

bool verify_token(const string &username,const string &token){
    Cache::ConstAccessor ac;
    if(token_cache->find(ac,String(username.c_str(),username.size()))){
        return token == *ac;
    }
    return false;
}

bool update_user(Database *db,const string & username,const string &origin_pwd,const string &new_pwd){
    string s;
    if(login(db,username,origin_pwd,s)){
        if(db->update(username,new_pwd)){
            Cache::ConstAccessor ac;
            if(user_cache->find(ac,String(username.c_str(),username.size())))
             {
                return true;
                user_cache->insert(String(username.c_str(),username.size()),new_pwd);
                //Update Cache
             }
            else
                user_cache->insert(String(username.c_str(),username.size()),new_pwd);
            return true;
        }
        else return false;
    }
    else
    return false;
}


bool add_user(Database *db,const string & username,const string &pwd){
    if(db->insert(username,pwd)){
        user_cache->insert(String(username.c_str(),username.size()),pwd);
        return true;
    }
    else
    return false;

}
