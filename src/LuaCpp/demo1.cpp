#include "oolua.h"
#include "Apple.h"
#include <iostream>
#include <fstream>
#include <boost/timer.hpp>
using std::cout;
using std::endl;
using std::ios;

// 注册
OOLUA_PROXY(Apple)
    OOLUA_MFUNC(cleanApple)
    OOLUA_MFUNC(eatApple)
    OOLUA_MFUNC(getWeight)
    OOLUA_MFUNC(cal)
    OOLUA_SFUNC(anyCFunc)   //This function will not be exported and needs to be registered with OOLua see OOLUA::register_class_static
OOLUA_PROXY_END

OOLUA_EXPORT_FUNCTIONS(Apple,cleanApple,eatApple,getWeight,cal)
OOLUA_EXPORT_FUNCTIONS_CONST(Apple)   

// 运行一段代码块
void callStaticMemFunc()
{
    OOLUA::Script* m_lua = new OOLUA::Script;
    m_lua->register_class<Apple>();
    m_lua->register_class_static<Apple>("anyCFunc", OOLUA::Proxy_class<Apple>::anyCFunc);

    Apple app;
    m_lua->run_chunk(
        "function func(a) return a:getWeight() end");
    m_lua->call("func", &app);

    double result(-1);
    OOLUA::pull(*m_lua, result);
    std::cout << "result = " << result << std::endl;
   
    delete(m_lua);
}

void luaCallCpp(OOLUA::Script * lua, int times)
{
    double start = 10;
    double result(-1);
    for(int i = 0; i < times; i++)
    {
        lua->call("testCalFunc", &start);
        OOLUA::pull(*lua, result);
    }
}
int main()
{
    //callStaticMemFunc();

    OOLUA::Script * lua = new OOLUA::Script;
    lua->register_class<Apple>();
    lua->register_class_static<Apple>("anyCFunc", OOLUA::Proxy_class<Apple>::anyCFunc);
    boost::timer t1;

    std::ofstream logfile;
    logfile.open("../config/release_oolua.csv", ios::out);

    bool ret_code;

    ret_code = lua->run_file("../config/cal.lua");
    /*ret_code = lua->run_chunk("function testCalFunc(num) a = Apple.new() num = a:cal(num) return num end");*/
    
    logfile << "加载lua脚本," << t1.elapsed() << "s\n";

    if (!ret_code)
    {
        cout <<"ERROR: " << lua_tostring(*lua, -1) << endl;
        lua_pop(*lua, 1);
        lua_close(*lua);
        exit(1);
    }

    for (int i = 1; i < 101; i++)
    {
        int times = 10000 * i;
        t1.restart();
        luaCallCpp(lua, times);
        logfile << times << "," << t1.elapsed() << "s\n";
    }

    delete(lua);
    logfile.close();
    system("pause");
    return 0;
}