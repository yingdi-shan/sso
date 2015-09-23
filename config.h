#ifndef CONFIG_H
#define CONFIG_H

#include "crow_all"
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Configure{
public:

	std::vector<string> server_ips;
	int server_number;

	Configure(char *filename){
		ifstream f(filename, ios::in);
		istreambuf_iterator<char> beg(f), end;
		string strdata(beg, end);
		f.close();

		auto x = crow::json::load(strdata);

		server_number = x["s_number"].i();
		for (int i=0; i< server_number; i++){
			server_ips.push_back(x["sso"][i].s());
		}

		#ifndef RELEASE
		for (int i=0; i<x["s_number"].i(); i++){
			cout << server_ips[i] << endl;
		}
		#endif
	}	
};

#endif
