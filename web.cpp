#include "crow_all"
#include "mysql.h"
#include "data_access.h"
#include<string>
#include<cstdlib>
using namespace std;
using namespace crow;

int main()
{
    App<CookieParser> app;

    CROW_ROUTE(app,"/")([&](const request& req){
        {
        /*
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
        */
        return "Welcome to SSO server.";
        }
    });
    Database *db = new Database();
    db->init("tcp://localhost:3306", "root", "test", "sso");
    init_user_cache(db);
    CROW_ROUTE(app, "/add_user")
    ([&](const crow::request & req){
        if(add_user(db,req.url_params.get("username"),req.url_params.get("pwd")))
        return "SUCCESS";
        else
        return "FAILURE";
    });

    CROW_ROUTE(app,"/update_user")
    ([&](const crow::request & req){
        if(update_user(db,req.url_params.get("username"),req.url_params.get("pwd"),req.url_params.get("new_pwd")))
        return "SUCCESS";
        else
        return "FAILURE";
    });

    CROW_ROUTE(app,"/verify_token")
    ([&](const crow::request & req){
        auto& ctx = app.get_context<CookieParser>(req);
        auto user_name = req.url_params.get("username");
        string&& token = ctx.get_cookie("TOKEN_ID");
        if(verify_token(user_name,token))
            return "SUCCESS";
        else
            return "FAILURE";
    });
    
    CROW_ROUTE(app,"/login").methods("POST"_method,"GET"_method)
    ([&](const crow::request & req){
        auto user_name = req.url_params.get("username");
        auto pwd = req.url_params.get("pwd");
        string token;
        if(login(db,string(user_name),string(pwd),token))
        {
            auto& ctx = app.get_context<CookieParser>(req);
            ctx.set_cookie("TOKEN_ID",token);
            return "SUCCESS";
        }
        else
            return "FAILURE";

    });

    app.port(8080).multithreaded().run();
    return 0;
}
