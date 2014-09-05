#include<iostream>
#include "oolua.h"
//#include "D:\ProgramFiles\liamdevine-oolua\liamdevine-oolua-a268fe00c4b9\unit_tests\test_classes\userdata_function_returns.h"

typedef struct Stub{
	
	Stub():m_a(0){}
	void increase_a()
	{
		m_a++;
		std::cout<< "Now the a is " << m_a << std::endl;
	}
	int return_a()
	{return m_a;}

	int m_a;
}Stub;

OOLUA_PROXY(Stub)
	OOLUA_MFUNC(increase_a)
	OOLUA_MFUNC(return_a)
	OOLUA_MGET(m_a)
OOLUA_PROXY_END

OOLUA_EXPORT_FUNCTIONS(Stub,increase_a,return_a)
OOLUA_EXPORT_FUNCTIONS_CONST(Stub,get_m_a)


typedef struct StubAsParam{
	StubAsParam():m_b(0){}
	StubAsParam(int b):
	m_b(b)
	{}
	void increase_b()
	{
		m_b++;
		std::cout<< "Now the b is " << m_b << std::endl;
	}
	int return_b()
	{return m_b;}

	int m_b;

}StubAsParam;

OOLUA_PROXY(StubAsParam)
	OOLUA_CTORS(
	OOLUA_CTOR(int))
OOLUA_MFUNC(increase_b)
OOLUA_MFUNC(return_b)
OOLUA_MGET(m_b)
OOLUA_PROXY_END

OOLUA_EXPORT_FUNCTIONS(StubAsParam,increase_b,return_b)
OOLUA_EXPORT_FUNCTIONS_CONST(StubAsParam,get_m_b)



class UseStub
{
public:
	OOLUA::Script * m_lua;
	UseStub()
		:m_int(0)
		,m_stub()
		
	{
		m_lua = new OOLUA::Script();
		m_stubp =new Stub();
		m_lua->register_class<Stub>();
		std::cout << "UseStub constructed" << std::endl;
	}
	Stub* funcReturnStub()
	{
		m_stubp->increase_a();
		return m_stubp;
	}//increase it in lua and set it to nil



	//Stub getStub()
	//{
	//	return m_stub;
	//}
	StubAsParam* testStubAsParam(StubAsParam* sp)// for function return traits
	{
		sp->increase_b();
		sp->return_b();
		return sp;
	}
	//int testStubAsParam(StubAsParam* & sp)//sp maybe null
	//{
	//	sp->increase_b();
	//	return sp->return_b();
	//}

	//void testVoidP(void * void_ptr){}

private:
	Stub* m_stubp;
	Stub m_stub;//class member type needs registration before using it.
	int m_int;
	
};
OOLUA_PROXY(UseStub)
	/*OOLUA_TAGS (No_default_constructor)
	OOLUA_CTORS(
	OOLUA_CTOR(OOLUA::Script*)
	)*/
	OOLUA_MEM_FUNC(lua_return<Stub*>,funcReturnStub)
	OOLUA_MEN_FUNC(lua_return<StubAsParam*>,testStubAsParam,out_p<StubAsParam*>)
OOLUA_PROXY_END

OOLUA_EXPORT_FUNCTIONS(UseStub,funcReturnStub)
OOLUA_EXPORT_FUNCTIONS_CONST(UseStub)

//lua_State * luaState = luaL_newstate();



int main()
{
	UseStub use;
	OOLUA::Script* s_trait = new OOLUA::Script();

	s_trait->register_class<UseStub>();
	s_trait->run_chunk("function func (obj)"
		"return obj:funcReturnStub"
		"end");
	s_trait->call("func",&use);
	std::cout << OOLUA::get_last_error(s_trait->state()) << std::endl;
	getchar();
	return 0;
}