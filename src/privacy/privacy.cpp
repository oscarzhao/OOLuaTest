#include "oolua.h"
#include <iostream>

//using namespace std;
//#	if OOLUA_USE_SHARED_PTR == 1
//#		include OOLUA_SHARED_HEADER
//#		include <csetjmp>
//
//#		ifdef _MSC_VER
//#			pragma warning(push)
//#			pragma warning(disable : 4702)//unreachable code
//#		endif
//namespace
//{
//	jmp_buf mark;
//	int OOLua_panic(lua_State* /*vm*/) //NOLINT(readability/casting)
//	{
//		longjmp(mark, 1);
//		return 0;
//	}
//} //namespace
//
//#		ifdef _MSC_VER
//#			pragma warning(pop)
//#		endif

int called = 0;
struct SharedFoo
{
	SharedFoo()
		: count(0)
	{}
	void no_param_function_const() const
	{
		printf("The count is: %d\n",count);
		++called;
	}
	void no_param_function()
	{
		++count;
		printf("The count is: %d\n",count);
	}
	void shared_param(OOLUA_SHARED_TYPE<SharedFoo> input)
	{
		m_shared = input;
	}
	void shared_param_ref(OOLUA_SHARED_TYPE<SharedFoo>& input)
	{
		m_shared = input;
	}
	OOLUA_SHARED_TYPE<SharedFoo> returnsSharedPtr()
	{
		return m_shared;
	}
	OOLUA_SHARED_TYPE<SharedFoo>& returnsRefToSharedPtr()
	{
		return m_shared;
	}
	void shared_param_type_is_const(OOLUA_SHARED_TYPE<SharedFoo const> input)
	{
		m_const_shared = input;
	}
	OOLUA_SHARED_TYPE<SharedFoo const> returnsSharedConstPtr()
	{
		return m_const_shared;
	}
	int count;
	OOLUA_SHARED_TYPE<SharedFoo> m_shared;
	OOLUA_SHARED_TYPE<SharedFoo const> m_const_shared;
};

OOLUA_PROXY(SharedFoo)
	OOLUA_MFUNC(no_param_function)
	OOLUA_MFUNC_CONST(no_param_function_const)
	OOLUA_MFUNC(shared_param)
	OOLUA_MFUNC(shared_param_ref)
	OOLUA_MFUNC(returnsSharedPtr)
	OOLUA_MFUNC(returnsRefToSharedPtr)
	OOLUA_MFUNC(shared_param_type_is_const)
	OOLUA_MFUNC(returnsSharedConstPtr)
	OOLUA_MEM_FUNC_RENAME(returns_maybe_null_shared
						, maybe_null<OOLUA_SHARED_TYPE<SharedFoo> >
						, returnsSharedPtr)
OOLUA_PROXY_END

OOLUA_EXPORT_FUNCTIONS(SharedFoo
						, no_param_function
						, shared_param
						, shared_param_ref
						, returnsSharedPtr
						, returnsRefToSharedPtr
						, shared_param_type_is_const
						, returnsSharedConstPtr
						, returns_maybe_null_shared)
OOLUA_EXPORT_FUNCTIONS_CONST(SharedFoo, no_param_function_const)


struct SharedConstructor{};

OOLUA_PROXY(SharedConstructor)
OOLUA_TAGS(Shared)
OOLUA_PROXY_END

OOLUA_EXPORT_NO_FUNCTIONS(SharedConstructor)


class testForShare
{
public:
	//OOLUA_SHARED_TYPE<int> m_int_p;
	OOLUA_SHARED_TYPE<testForShare> t_shared;
	testForShare():count(0)
		//,m_int_p(new int(10))
		//,t_shared(new testForShare)
	{}
	void do_something()
	{
		std::cout << "It is doing something.\n";
	}
private:
	int count;

};

OOLUA_PROXY(testForShare)
OOLUA_MGET(t_shared)
OOLUA_MFUNC(do_something)
//OOLUA_MGET(m_int_p) //can't be compiled if not annotated (the 1st problem)
OOLUA_PROXY_END

OOLUA_EXPORT_FUNCTIONS(testForShare,do_something)
OOLUA_EXPORT_FUNCTIONS_CONST(testForShare,get_t_shared)

OOLUA::Script* m_lua = new OOLUA::Script(); 
static void call_pushSharedObjectAndCallFunction_countMemberEqualsOne()
{
	
	m_lua->register_class<SharedFoo>();
	OOLUA_SHARED_TYPE<SharedFoo> foo(new SharedFoo);
	m_lua->run_chunk("return function(obj) obj:returns_maybe_null_shared()  end");
		//no_param_function() end");
	int ret = m_lua->call(1, foo);
	std::cout << OOLUA::get_last_error(*m_lua) << std::endl;
}

int main()
{
	//call_pushSharedObjectAndCallFunction_countMemberEqualsOne();

	OOLUA::Script vm;
	vm.register_class<testForShare>();
	OOLUA_SHARED_TYPE<testForShare>t(new testForShare);
	//vm.run_chunk("return function(obj)"
	//	//"obj:get_t_shared()"
	//	"obj:do_something()"
	//	"print('Hi')"
	//	"end");
	int result = vm.call(1,t);
	std::cout << OOLUA::get_last_error(vm) << std::endl;

	system("pause");
	return 0;
}

//#endif