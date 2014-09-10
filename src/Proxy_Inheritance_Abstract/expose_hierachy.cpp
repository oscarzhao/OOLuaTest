#include "expose_hierachy.h"
#include "oolua_dsl_export.h"

OOLUA_EXPORT_FUNCTIONS(AbstractBase, doSomething)
OOLUA_EXPORT_FUNCTIONS_CONST(AbstractBase, doSomethingConst)

OOLUA_EXPORT_FUNCTIONS(RetDerived)
OOLUA_EXPORT_FUNCTIONS_CONST(RetDerived)

OOLUA_EXPORT_FUNCTIONS(Derived, funcVoidNoParam, funcVoidThreeIntParams)
OOLUA_EXPORT_FUNCTIONS_CONST(Derived)

OOLUA_EXPORT_FUNCTIONS(MyClass, getRetDerived)
OOLUA_EXPORT_FUNCTIONS_CONST(MyClass)