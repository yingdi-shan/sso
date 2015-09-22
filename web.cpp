#include "crow_all"
#include "mysql.h"
#include<string>
#include<cstdlib>
using namespace std;
using namespace crow;

int main()
{
    App<CookieParser> app;

    CROW_ROUTE(app,"/")([&](const request& req){
        {
            auto& ctx = app.get_context<CookieParser>(req);
            string ret = ctx.get_cookie("key");


            if(ret==""){
                ctx.set_cookie("key","1");
                return "Time Counter 1";
            }
            else
            {
                ostringstream os;
                int cur_time = atoi(ret.c_str());
                os<<cur_time+1;
                ctx.set_cookie("key",os.str());
                os.str("");
                os.clear();
                os<<"Counter "<<cur_time+1;
                return os.str().c_str();
            }

        }
    });
/*
 CROW_ROUTE(app, "/add_json")
    ([](const crow::request& req){
        auto x = crow::json::load(req.body);
        if (!x)
            return crow::response(400);
        int sum = x["a"].i()+x["b"].i();
        std::ostringstream os;
        os << sum;
        return crow::response{os.str()};
    });
*/
    Database *db = new Database();
    db->init("tcp://localhost:3306", "root", "test", "sso");
    CROW_ROUTE(app, "/add_user")
    ([&](const crow::request & req){
        db->insert(req.url_params.get("username"),req.url_params.get("pwd"));
        return "SUCCESS";
    });


    app.port(8080).multithreaded().run();
    return 0;
}
