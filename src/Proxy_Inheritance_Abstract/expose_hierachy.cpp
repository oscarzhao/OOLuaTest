#include "expose_hierachy.h"
#include "oolua_dsl_export.h"

OOLUA_EXPORT_FUNCTIONS(AbstractBase)
OOLUA_EXPORT_FUNCTIONS_CONST(AbstractBase, getClassName)

OOLUA_EXPORT_FUNCTIONS(RetDerived, funcVoidNoParam, funcVoidThreeIntParams)
OOLUA_EXPORT_FUNCTIONS_CONST(RetDerived)

OOLUA_EXPORT_FUNCTIONS(Derived, funcVoidNoParam, funcVoidThreeIntParams)
OOLUA_EXPORT_FUNCTIONS_CONST(Derived)

OOLUA_EXPORT_FUNCTIONS(MyClass, getRetDerived)
OOLUA_EXPORT_FUNCTIONS_CONST(MyClass)