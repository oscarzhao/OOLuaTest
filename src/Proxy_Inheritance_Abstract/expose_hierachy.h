#ifndef HIERACHY_EXPOSE_H_
#define HIERACHY_EXPOSE_H_

#include "cpp_hierachy.h"

OOLUA_PROXY(AbstractBase)
    OOLUA_TAGS(Abstract)
    //OOLUA_MEM_FUNC(void, doSomething)
    //OOLUA_MEM_FUNC_CONST(void, doSomethingConst)
    OOLUA_MFUNC_CONST(getClassName)
OOLUA_PROXY_END

OOLUA_PROXY(RetDerived, AbstractBase)
    OOLUA_MEM_FUNC(void, funcVoidNoParam)
    OOLUA_MEM_FUNC(void, funcVoidThreeIntParams, int, int, int)
OOLUA_PROXY_END

OOLUA_PROXY(Derived, AbstractBase)
    OOLUA_MEM_FUNC(void, funcVoidNoParam)
    OOLUA_MEM_FUNC(void, funcVoidThreeIntParams, int, int, int)
OOLUA_PROXY_END

OOLUA_PROXY(MyClass)
    OOLUA_MEM_FUNC(RetDerivedPtr, getRetDerived)
OOLUA_PROXY_END
#endif