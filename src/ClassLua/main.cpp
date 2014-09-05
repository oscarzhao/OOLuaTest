#include <iostream>
#include <fstream>
#include <boost/timer.hpp>
#include <boost/shared_ptr.hpp>

#include "oolua.h"
#include "expose_apple.h"
/**
 *	测试 OOLUA pull 和 push 的使用
 */
using std::cout;
using std::endl;
using std::ios;
void printApple(const Apple & app)
{
    cout << "Weight: " << app.getWeight() << " kg\n";
    cout << "Color:  " << app.getColor() << endl;
}
int main()
{
    OOLUA::Script* vm = new OOLUA::Script;
    vm->register_class<Apple>();

    vm->run_chunk("function func() return Apple.new() end");
    vm->call("func");

    /*OOLUA::cpp_acquire_ptr<Apple *> result;*/
    Apple * result;
    OOLUA::pull(*vm, result);

    boost::shared_ptr<Apple> appPtr = boost::shared_ptr<Apple>(new Apple(100, "Green", true));
    OOLUA::push(*vm, appPtr);

    Apple * res2;
    OOLUA::pull(*vm, res2);

    //OOLUA::push(*vm, b);
    //OOLUA::pull(*vm, c);

    // 基本类型 可以压入弹出
    //OOLUA::push(*vm, "stop please");
    //std::string result;
    //OOLUA::pull(*vm, result);

    //Apple a(*(result.m_ptr));
    //delete(result.m_ptr)；
    printApple(*result);
    printApple(*res2);
    //delete result;   // 执行这个语句会报错
    //delete res2;

    delete(vm);
    system("pause");
    return 0;
}