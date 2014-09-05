extern "C"
{
#include <lua/lua.h>   // Lua 语言解释器
#include <lua/lualib.h>  // Lua 标准库
#include <lua/lauxlib.h>  // Lua辅助工具
};

char * code = "for i = 0, 5 do print(\'Hello, World!\') end";

int main()
{
    lua_State * s = luaL_newstate();            // 建立一个虚拟机
    luaL_openlibs(s);                           // 打开 Lua 附加 库
    luaL_dostring(s, code);                     // 执行字符串中源代码
    lua_close(s);                                // 关闭虚拟机

    getchar();
    return 0;
}