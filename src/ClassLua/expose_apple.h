#ifndef EXPOSE_APPLE_INT_H_
#	define EXPOSE_APPLE_INT_H_

#	include "Apple.h"
#	include "oolua_dsl.h"

// зЂВс
OOLUA_PROXY(Apple)
    OOLUA_CTORS(
        OOLUA_CTOR(double, std::string, bool)
    )
    OOLUA_MFUNC(cleanApple)
    OOLUA_MFUNC(eatApple)
    OOLUA_MFUNC_CONST(getWeight)
    OOLUA_MFUNC_CONST(getColor)
    OOLUA_MFUNC(cal)
    OOLUA_SFUNC(anyCFunc)   //This function will not be exported and needs to be registered with OOLua see OOLUA::register_class_static
OOLUA_PROXY_END

#endif
