#include <iostream>

#include "oolua.h"
/*
Name: HelloMoon
Function: 打印 "Hello Lua"
Remark: OOLUA 第一个例子
*/

void say(char const * input)
{
    printf("\"%s\", she says\n", input);
}

OOLUA_CFUNC(say, l_say)

void hello_minimalist_function()
{
    using namespace OOLUA;  // NOLINT(build/namespaces)
    Script vm;
    set_global(vm, "she_says", l_say);
    run_chunk(vm, "she_says('You are a good guy')");
    // or
    // vm.run_chunk("she_says('You are a good guy')");
}

int main()
{
    hello_minimalist_function();
    system("pause");
    return 0;
}