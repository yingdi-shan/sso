#include <boost/network/protocol/http/client.hpp>
#include "config.h"
#include <string>
#include <sstream>
#include <vector>
#include "util.h"
#include <iostream>

using namespace std;

using namespace boost::network;


int main(){
	Configure *conf = new Configure("config.txt");
//	string s = "hello";
//	cout << hash_str(s) << endl;

	crow::SimpleApp app;

    CROW_ROUTE(app, "/")([conf](){
    	return "hello";
    });

    CROW_ROUTE(app, "/add_user")
    ([&](const crow::request & req){
    	std::string username = req.url_params.get("username");
    	std::string pwd = req.url_params.get("pwd");
		
		int i = hash_str(username)%conf->server_number;
		std::string url = "http://";
		url += conf->server_ips[i];
		url += "/add_user?username=" + username;
		url += "&pwd=" + pwd;
    	
    	http::client client;
    	http::client::request request(url);
    	cout << "start request " << url << endl;
    	http::client::response response = client.get(request);
    	auto s = body(response);
 		
 		cout << "request end" << endl;
 		//cout << s << endl;
     	return "success";
    });



    app.port(18080).multithreaded().run(); 
	
	return 0;
}