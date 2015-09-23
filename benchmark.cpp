#include <boost/network/protocol/http/client.hpp>
#include <iostream>
#include <thread>
#include <string>
#include <memory>
#include <random>
#include <atomic>
#include <chrono>
#include <atomic>
#include <ctime>
#include <fstream>
#include <vector>

using namespace std;

atomic<int> x;
atomic<int> failtime;

char* hostname; 
int testtime;
int mod;

vector<pair<string, string> > userlist;

void remote_login(){
    using namespace boost::network;
    using namespace boost::network::http;

    try{
        client::request request_(hostname);
        request_ << header("Connection", "close");
        client client_;
        client::response response_ = client_.get(request_);
        std::string body_ = body(response_);
        int fault_time=0;
        x++;
    }catch( std::exception & e){
        failtime++;
        cout << "exception" << endl;
    }

}

void update(){
    using namespace boost::network;
    using namespace boost::network::http;

    try{
        client::request request_(hostname);
        request_ << header("Connection", "close");
        client client_;
        client::response response_ = client_.get(request_);
        std::string body_ = body(response_);
        int fault_time=0;
        x++;
    }catch( std::exception & e){
        failtime++;
        cout << "exception" << endl;
    }

}

void verify(){
    using namespace boost::network;
    using namespace boost::network::http;

    try{
        client::request request_(hostname);
        request_ << header("Connection", "close");
        client client_;
        client::response response_ = client_.get(request_);
        std::string body_ = body(response_);
        int fault_time=0;
        x++;
    }catch( std::exception & e){
        failtime++;
        cout << "exception" << endl;
    }

}
void login(){
    using namespace boost::network;
    using namespace boost::network::http;

    try{
        client::request request_(hostname);
        request_ << header("Connection", "close");
        client client_;
        client::response response_ = client_.get(request_);
        std::string body_ = body(response_);
        int fault_time=0;
        x++;
    }catch( std::exception & e){
        failtime++;
        cout << "exception" << endl;
    }
}
void add_user(){
    using namespace boost::network;
    using namespace boost::network::http;

    try{
        client::request request_(hostname);
        request_ << header("Connection", "close");
        client client_;
        client::response response_ = client_.get(request_);
        std::string body_ = body(response_);
        int fault_time=0;
        x++;
    }catch( std::exception & e){
        failtime++;
        cout << "exception" << endl;
    }
}

void threadMain(){
    auto Start = std::chrono::steady_clock::now( );

    while(std::chrono::steady_clock::now() < Start + std::chrono::milliseconds( testtime )){
        switch(mod){
            case 0:
                add_user();
                break;
            case 1:
                login();
                break;
            case 2:
                verify();
                break;
            case 3:
                update();
                break;
            case 4:
                remote_login();
                break;
            default:
                return;
                break;
        }
        
    }
}


int main(int argc, char** argv){
        fstream fin("data/http.txt");
        string line;
        while(getline(fin, line)){
            cout << line << endl;
            string username = line.substr(0, 8);
            string pwd = line.substr(9, 17);
            userlist.push_back(pair<string, string>(username, pwd));
        }


        if(argc == 1){
            hostname = "http://0.0.0.0:5000/login?username=lmx&pwd=123";
        }else{
            hostname = argv[1];
            cout << hostname << endl;
        }
/*    
        int numThreads=atoi(argv[2]);
        testtime = atoi(argv[3]);
        mod = atoi(argv[4]);

        std::vector<std::thread> threads;

        using namespace std::chrono;
        steady_clock::time_point t1 = steady_clock::now();
        cout << "start " << endl; 

        for (int i = 0; i < numThreads; i++) {
            threads.push_back(std::thread(threadMain));
        }
        
        for (int i = 0; i < numThreads; i++) {
            threads[i].join();
        }

        steady_clock::time_point t2= steady_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
        cout << "time: " << time_span.count() <<endl;
        cout << "requests " << x << endl;
 */

    return 0;
}

