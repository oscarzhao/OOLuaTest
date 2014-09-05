#include "oolua.h"
#include <iostream>
#include <string>
#include <stdio.h>

void say(char const* input)
{
	printf("%s from a standalone function\n",input);
}
OOLUA_CFUNC(say,l_say)
typedef struct stub{
	int a;
	void foo(){a++;}
}stub; 
class Apple
{	
public:
	Apple(void):
	  m_weight(200),
		  m_color("red"),
		  m_clean(false)	
	  {
		  std::cout << "Apple constructed successfully!" <<std::endl;
	  }
	  ~Apple(void)
	  {
		  std::cout << "Apple destructed." <<std::endl;
	  }
	  void cleanApple()
	  {
		  m_clean = true;
		  std::cout <<"The  apple is clean now !"<<std::endl;
	  }
	  double eatApple(double bitten)
	  {	
		  m_weight -= bitten;
		  return m_weight;
	  }
	  static double anyCFunc (double x)
	  {
		  x += 1;
		  std::cout << x <<	std::endl;
		  return x;
	  }
	  double getWeight()
	  {
		  return m_weight;
	  }

	  
private:
	double m_weight;
	std::string m_color;
	bool m_clean;
};

OOLUA_PROXY(Apple)
	OOLUA_MFUNC(cleanApple)
	OOLUA_MFUNC(eatApple)
	OOLUA_MFUNC(getWeight)
	OOLUA_SFUNC(anyCFunc)   //This function will not be exported and needs to be registered with OOLua see OOLUA::register_class_static
OOLUA_PROXY_END

OOLUA_EXPORT_FUNCTIONS(Apple,cleanApple,eatApple,getWeight)
OOLUA_EXPORT_FUNCTIONS_CONST(Apple)

void expressive_say(char const* input)
{
	printf("%s from a expressive function\n", input);
}
void expressive_say(int input)
{
	printf("Huh %d\n", input);
	//CPPUNIT_ASSERT(0);
}

OOLUA_CFUNC( (( void(*)(char const*))expressive_say), cast_expressive_say)

void hello_cast_minimalist_function()
{
	using namespace OOLUA; //NOLINT(build/namespaces)
	Script vm;
	set_global(vm, "say", cast_expressive_say);
	vm.run_chunk("say('Hello Lua, we are a cast function not')");
}


int main()
{
	OOLUA::Script s_moon;
	set_global(s_moon,"say",l_say);
	run_chunk(s_moon,"say('Hello Moon!')");
/*


//\brief Helper function to set a Lua global variable.
//\tparam T Type for instance
//\param[in] vm lua_State
//\param[in] name Global name to set
//\param[in] instance Any variable which is valid to push to the stack
//\return Boolean indicating if the operation was successful \see OOLuaErrorReporting


template<typename T>
bool set_global(lua_State* vm, char const* name, T& instance)
{
if ( !OOLUA::push(vm, instance) ) return false;
lua_setglobal(vm, name);
return true;
}


		//\brief None template version
		//\details Enables setting a global with a value of lua_CFunction without
		//requiring you make a reference to the function.
		//\param[in] vm The lua_State to work on
		//\param[in] name String which is used for the global name
		//\param[in] instance The lua_CFuntion which will be set at the global value for name
	
using namespace OOLua
bool set_global(lua_State* vm, char const* name, lua_CFunction instance)
{
lua_pushcclosure(vm, instance, 0);
lua_setglobal(vm, name);
return true;
}



*/
	//OOLUA::Script s_plus;
	//s_plus.run_file("plus.lua");
	//s_plus.call("plus",1,2);

	hello_cast_minimalist_function();

	OOLUA::Script s_apple;
	Apple apple;
	s_apple.register_class<Apple>();
	s_apple.register_class_static<Apple>("anyCFunc",OOLUA::Proxy_class<Apple>::anyCFunc);//register static function in Lua
	/*s_apple.run_chunk(
		"a=Apple.new()"
		"a:cleanApple()"
		"w = a:getWeight()"
		"print(w)"
		"w = a:eatApple(20)"
		"print(w)"
		"print('Hi!')");*/

	s_apple.run_chunk(
		"function func(a)"
		"a:cleanApple()"
		"w = a:getWeight()"
		"print(w)"
		"w = a:eatApple(20)"
		"print(w)"
		//"a = nil"
		"print('Hi!')"
		"end");

	s_apple.call("func",&apple);//load + 1 can't be called 
	OOLUA::Lua_func_ref lua_func;

	std::cout << OOLUA::get_last_error(s_apple) << std::endl;

	OOLUA::Lua_func_ref func_ref;
	lua_State * s_ref =lua_newthread(s_apple.state());
	OOLUA::load_chunk(s_ref,
		"print('Hello from function reference!')"
		"return"
		);
	OOLUA::pull(s_ref,func_ref);
	OOLUA::Lua_function caller(s_apple);
	caller(func_ref);
	std::cout << OOLUA::get_last_error(s_apple) << std::endl;

	//static bool pull(lua_State* const vm, T &  value)
	//{
	//	//enumeration type so a static cast should be allowed else this
	//	//is being called with the wrong type
	//	typedef char dummy_can_convert [ LVD::can_convert_to_int<T>::value ? 1 : -1];
	//	//value = static_cast<T>( lua_tonumber( vm, -1) );
	//	if( !cpp_runtime_type_check_of_top(vm, lua_isnumber, "enum type") )
	//		return false;
	//	value = static_cast<T>(lua_tointeger(vm, -1));
	//	lua_pop(vm, 1);
	//	return true;
	//}

	system("pause");
	return 0;
}