#include <iostream>
#include <string>
#include "oolua.h"
#include "cpp_hierachy.h"
#include "expose_hierachy.h"

///*
//Name: Proxy
//Function: 使用 Proxy ，C++ 继承
//Remark: OOLUA 第五个例子
//*/

static void stackDump(lua_State* L)
{
    int i;
    int top = lua_gettop(L);
    for (i = 1; i <= top; i++)
    {
        int t = lua_type(L, i);
        switch(t){
            case LUA_TSTRING:
                std::cout << "'" << lua_tostring(L, i) << "'";
                break;
            case LUA_TBOOLEAN:
                std::cout << lua_toboolean(L, i)? "true": "false";
                break;
            case LUA_TNUMBER:
                std::cout << lua_tonumber(L, i);
                break;
            default:
                std::cout << lua_typename(L, t);
                break;
        }

        std::cout << "    "; // put a separator
    }
    std::cout << std::endl;
}

int main()
{
    //cleanAppleTest();
    OOLUA::Script* m_lua = new OOLUA::Script;
    m_lua->register_class<AbstractBase>();
    m_lua->register_class<RetDerived>();
    m_lua->register_class<Derived>();
    m_lua->register_class<MyClass>();

    m_lua->run_chunk(
        "function func() "
        "a=MyClass() " 
        "return a:getRetDerived() "
        //"w = ptr.funcVoidThreeIntParams(1,2,3)"
        "end ");
    m_lua->call("func");

    delete(m_lua);

    system("pause");
    return 0;
}