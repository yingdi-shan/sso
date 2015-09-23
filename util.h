#ifndef UTIL_H

#define UTIL_H

#include <string>

using namespace std;

int hash_str(string s){
	int a = 0;
	for(int i=0; i<s.size(); i++){
		a = a*33 + (s[i]-'a');
		a = a%1024; 
	}
	return a;
}

#endif