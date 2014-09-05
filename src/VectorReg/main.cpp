#include <iostream>
#include <fstream>
#include <boost/timer.hpp>

#include "oolua.h"
#include "expose_vector.h"

using std::cout;
using std::endl;
using std::ios;

int main()
{
    //callStaticMemFunc();

    OOLUA::Script * lua = new OOLUA::Script;
    lua->register_class<vector_int>();

    vector_int intVec;
    intVec.push_back(1);
    intVec.push_back(2);
    intVec.push_back(3);

    bool ret_code;
    ret_code = lua->run_file("../config/vectorRegist.lua");
    if (!ret_code)
    {
        cout <<"ERROR: " << lua_tostring(*lua, -1) << endl;
        lua_pop(*lua, 1);
        lua_close(*lua);
        exit(1);
    }

    lua->call("testBase", &intVec);
    int res;
    OOLUA::pull(*lua, res);
    std::cout << "vector size = " << res << std::endl;

    delete(lua);
    system("pause");
    return 0;
}