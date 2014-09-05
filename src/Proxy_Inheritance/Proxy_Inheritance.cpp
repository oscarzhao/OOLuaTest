#include <iostream>
#include <string>
#include "oolua.h"
#include "FruitApple.h"
#include "FruitApple_expose.h"

///*
//Name: Proxy
//Function: 使用 Proxy ，C++ 继承
//Remark: OOLUA 第五个例子
//*/

namespace{
    bool get_result(OOLUA::Script* lua)
    {
        bool result;
        OOLUA::pull(*lua, result);
        return result;
    }

    template<typename T>
    std::auto_ptr<T> get_class(OOLUA::Script* lua)
    {
        OOLUA::cpp_acquire_ptr<T*> result;
        OOLUA::pull(*lua, result);
        return std::auto_ptr<T>(result.m_ptr);
    }

    template<typename T, typename T1>
    void operator_script(OOLUA::Script* lua, T& lhs, T1& rhs, std::string const& op)
    {
        std::string func(std::string("func = function(lhs,rhs) return lhs ")
            + op
            + std::string(" rhs end"));
        lua->run_chunk(func);
        lua->call("func", &lhs, &rhs);
    }
} // namespace

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

// 这里并没有 在 lua 中调用 注册的 C++ 类和方法
void cleanAppleTest()
{
    OOLUA::Script* m_lua = new OOLUA::Script;
    m_lua->register_class<Apple>();
    Apple apple;
    OOLUA::push(*m_lua, &apple);
    get_class<Apple>(m_lua)->anyCFunc(2);
    delete(m_lua);
}

void callMemFunc()
{
    OOLUA::Script * m_lua = new OOLUA::Script;
    m_lua->register_class<Apple>();
    std::string luaScript = std::string("");
    delete m_lua;
}
void callStaticMemFunc()
{
    OOLUA::Script* m_lua = new OOLUA::Script;
    m_lua->register_class<Apple>();
    m_lua->register_class_static<Apple>("AnyCFunc", OOLUA::Proxy_class<Apple>::anyCFunc);

    // fine, works well
    //bool result = m_lua->run_chunk("Apple.AnyCFunc(1)");
    //std::cout << "result: " << result << std::endl;
    
    // not fine, copy fails
    m_lua->run_chunk(
        "function func()"
        "a = Apple()" 
        "w = a:getWeight()"
        "return w"
        "end");
    m_lua->call("func");
    //m_lua->call("func", &app);

    // 测试 加载 程序块，使用 call
    //m_lua->load_chunk("return");
    //lua_pushvalue(*m_lua, 1);
    //OOLUA::Lua_function caller(*m_lua);
    //std::cout << "return " << caller(1) << std::endl;
    delete(m_lua);
}
int main()
{
    //cleanAppleTest();
    callStaticMemFunc();
    system("pause");
    return 0;
}