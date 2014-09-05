#include <iostream>
#include <string>
#include "oolua.h"
#include <include/cppunit/extensions/HelperMacros.h>
//
///*
//Name: Proxy
//Function: 使用 Proxy, 最简单的例子（没有输出）
//Remark: OOLUA 第三个例子
//*/
//
//// 声明一个 类 或者 struct
//struct Stub1{
//};
//
//// Proxy Block
//// first, create a proxy block which starts with a OOLUA_PROXY call to which you pass the
////        name of the C++ class to be proxied, this block ends at the next OOLU_PROXY_END
//OOLUA_PROXY(Stub1)
//OOLUA_PROXY_END
//
//// Exporting
//// second, export the member functions which are to be made available for the type in Lua.
////         Exporting defines which member functions will be registered with Lua when the class
////         type is registered.  Even when there are no member functions to be exported you still
////         need to inform OOLua about this.  Calling on an OOLUA_EXPORT* procedure in a header
////         file is an error that will fail to compile
//OOLUA_EXPORT_NO_FUNCTIONS(Stub1)
//
//// Registering
//// Lastly, regiester the type with a lua_State after which the type can be created and used in Lua
//OOLUA::Script* m_lua = new OOLUA::Script();
//void setUp()
//{
//    m_lua->register_class<Stub1>();
//}
//void new_luaCreateInstance_noException()
//{
//    CPPUNIT_ASSERT_NO_THROW(m_lua->run_chunk("Stub1.new()"));
//}
////int main()
////{
////    setUp();
////    new_luaCreateInstance_noException();
////    system("pause");
////}