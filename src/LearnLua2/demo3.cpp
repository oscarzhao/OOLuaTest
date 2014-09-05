extern "C"
{
#include <lua/lua.h>   // Lua 语言解释器
#include <lua/lualib.h>  // Lua 标准库
#include <lua/lauxlib.h>  // Lua辅助工具
};
#include <iostream>
#include <string>

int main()
{
    lua_State * s = luaL_newstate();            // 建立一个虚拟机
    luaL_openlibs(s);                           // 打开 Lua 附加库
    // 需要 将 demo3.lua 放到Working Directory 下面，才可以读到
    int ret = luaL_dofile(s, "../../src/LearnLua2/demo3.lua");                // 执行文件中的源代码

    if(0 != ret)
    {
        std::string strErr = lua_tostring(s, -1);
        std::cout << strErr << std::endl;
        lua_pop(s, 1);
    }
    
    lua_getglobal(s, "show");  //               // 将Lua全局变量入栈
    lua_pushstring(s, "It is from C++");        // 将字符串入栈
    lua_call(s, 1, 1);                          // 调用 Lua函数
    const char *result = lua_tostring(s, -1);   // 获取栈顶的返回值

    std::cout << "C++ has got: " << result << std::endl;
    lua_pop(s, 1);

    lua_close(s);                                // 关闭虚拟机
    return 0;
}