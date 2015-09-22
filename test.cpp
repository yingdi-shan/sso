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

using namespace tstarling;
typedef tstarling::ThreadSafeStringKey String;
typedef String::HashCompare HashCompare;
typedef tstarling::ThreadSafeLRUCache<String, int, HashCompare> Cache;

std::unique_ptr<Cache> cache = std::unique_ptr<Cache>(new Cache(1000000));
using namespace std;
vector<String> strings;
String randomstring(){
	char str[11];
	for (int i=0; i<10; i++){
		str[i] = 'a' + rand()%26;
	}
	str[10] = '\0';
	return String(str,10);
}


void threadMain() {
     //printf("Hello\n");
      Cache::ConstAccessor ac;
      for (int j = 0; j < 100; j++) {
      //sum+=j*j;
        cache->insert(strings[rand()%100000],j);
      }
    for (int j = 0; j < 1000; j++) {
      //sum+=j*j;
        cache->find(ac,strings[rand()%100000]);
      }


}

int main(){

    int numThreads=2000;
    std::vector<std::thread> threads;

    for(int i=0;i<100000;i++)
    strings.push_back(randomstring());

    cout<<"begin"<<endl;
    for (int i = 0; i < numThreads; i++) {
        threads.push_back(std::thread(threadMain));
    }

    for (int i = 0; i < numThreads; i++) {
      threads[i].join();
    }
    cout<<"end"<<endl;

	return 0;
}
