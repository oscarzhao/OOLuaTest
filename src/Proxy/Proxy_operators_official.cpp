//#include <iostream>
//#include <string>
//#include "oolua.h"
//#include <include/cppunit/extensions/HelperMacros.h>
//
/////*
////Name: Proxy
////Function: 使用 Proxy 的运算符
////Remark: OOLUA 第四个例子
////*/
//
//namespace{
//    bool get_result(OOLUA::Script* lua)
//    {
//        bool result;
//        OOLUA::pull(*lua, result);
//        return result;
//    }
//
//    template<typename T>
//    std::auto_ptr<T> get_class(OOLUA::Script* lua)
//    {
//        OOLUA::cpp_acquire_ptr<T*> result;
//        OOLUA::pull(*lua, result);
//        return std::auto_ptr<T>(result.m_ptr);
//    }
//
//    template<typename T, typename T1>
//    void operator_script(OOLUA::Script* lua, T& lhs, T1& rhs, std::string const& op)
//    {
//        std::string func(std::string("func = function(lhs,rhs) return lhs ")
//            + op
//            + std::string(" rhs end"));
//        lua->run_chunk(func);
//        lua->call("func", &lhs, &rhs);
//    }
//} // namespace
//
//// 声明一个 类 或者 struct
//class Class_ops
//{
//public:
//    Class_ops(int const & i):m_i(i){}
//    Class_ops():m_i(0){}
//    Class_ops(Class_ops const & rhs): m_i(rhs.m_i){}
//
//    int const & geti() const
//    {
//        return m_i;
//    }
//
//    bool operator == (Class_ops const & rhs) const
//    {
//        return m_i == rhs.m_i;
//    }
//
//    bool operator < (Class_ops const & rhs) const
//    {
//        return m_i < rhs.m_i;
//    }
//
//    bool operator <= (Class_ops const & rhs) const
//    {
//        return m_i <= rhs.m_i;
//    }
//
//    Class_ops operator + (Class_ops const & rhs) const
//    {
//        return Class_ops(m_i + rhs.m_i);
//    }
//
//    Class_ops operator * (Class_ops const & rhs) const
//    {
//        return Class_ops(m_i * rhs.m_i);
//    }
//
//    Class_ops operator - (Class_ops const & rhs) const
//    {
//        return Class_ops(m_i - rhs.m_i);
//    }
//
//    Class_ops operator / (Class_ops const & rhs) const
//    {
//        return Class_ops(m_i / rhs.m_i);
//    }
//private:
//    int m_i;
//};
//
//// Proxy Block
//// first, create a proxy block which starts with a OOLUA_PROXY call to which you pass the
////        name of the C++ class to be proxied, this block ends at the next OOLU_PROXY_END
//OOLUA_PROXY(Class_ops)
//    OOLUA_TAGS(
//        Equal_op
//        , Less_op
//        , Less_equal_op
//        , Add_op
//        , Sub_op
//        , Mul_op
//        , Div_op
//    )
//    OOLUA_MFUNC_CONST(geti)
//OOLUA_PROXY_END
//
//// Exporting
//// second, export the member functions which are to be made available for the type in Lua.
////         Exporting defines which member functions will be registered with Lua when the class
////         type is registered.  Even when there are no member functions to be exported you still
////         need to inform OOLua about this.  Calling on an OOLUA_EXPORT* procedure in a header
////         file is an error that will fail to compile
//OOLUA_EXPORT_FUNCTIONS(Class_ops)
//OOLUA_EXPORT_FUNCTIONS_CONST(Class_ops, geti)
//
//
//void testProxyOperators()
//{
//    Class_ops lhs(0);
//    Class_ops rhs(899);
//    // Registering
//    // Lastly, register the type with a lua_State after which the type can be created and used in Lua
//    OOLUA::Script* m_lua = new OOLUA::Script();
//    m_lua->register_class<Class_ops>();
//
//    operator_script(m_lua, lhs, rhs, "<");
//    bool result = get_result(m_lua);
//    std::cout << "result: " << result << std::endl;
//    delete m_lua;
//}
////int main()
////{
////    testProxyOperators();
////    system("pause");
////    return 0;
////}