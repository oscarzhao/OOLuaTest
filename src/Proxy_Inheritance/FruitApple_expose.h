#ifndef FRUIT_APPLE_EXPOSE_H_
#define FRUIT_APPLE_EXPOSE_H_

#include "FruitApple.h"
//OOLUA_PROXY(Fruit)
//OOLUA_PROXY_END
OOLUA_PROXY(Apple)
    OOLUA_MFUNC(cleanApple)
    OOLUA_SFUNC(anyCFunc)   //This function will not be exported and needs to be registered with OOLua see OOLUA::register_class_static
OOLUA_PROXY_END

#endif