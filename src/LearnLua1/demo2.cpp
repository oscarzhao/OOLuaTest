extern "C"
{
#include <lua/lua.h>   // Lua 语言解释器
#include <lua/lualib.h>  // Lua 标准库
#include <lua/lauxlib.h>  // Lua辅助工具
};
#include <iostream>
#include <string>

int divide(lua_State * s) // 供 Lua使用的函数通用原型
{
    double a = lua_tonumber(s, -2);   // 取得第一个参数
    double b = lua_tonumber(s, -1);   // 取得第二个参数
    int quot = int(a)/int(b);
    int rem = int(a)%int(b);
    lua_pushnumber(s, quot);   // 将第一个返回值入栈
    lua_pushnumber(s, rem);    // 将第二个返回值入栈
    return 2;
}

int main()
{
    lua_State * s = luaL_newstate();            // 建立一个虚拟机
    luaL_openlibs(s);                           // 打开 Lua 附加库
    
    lua_register(s, "div", divide);             // 向虚拟机注册变量
    // 需要将 demo2.lua 放到Working Directory 下面，才可以读到
    int ret = luaL_dofile(s, "../../src/LearnLua1/demo2.lua");                // 执行文件中的源代码

    if(0!=ret)
    {
        std::string strErr = lua_tostring(s, -1);
        std::cout << strErr<< std::endl;
        lua_pop(s, 1);
    }


    //std::string error = lua_tostring(s, -1);
    //std::cout << error;

    lua_close(s);                                // 关闭虚拟机
    return 0;
}