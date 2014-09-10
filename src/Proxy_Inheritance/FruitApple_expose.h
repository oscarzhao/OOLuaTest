#ifndef FRUIT_APPLE_EXPOSE_H_
#define FRUIT_APPLE_EXPOSE_H_

#include "FruitApple.h"

OOLUA_PROXY(Fruit)
OOLUA_MFUNC(getWeight)
OOLUA_PROXY_END

// if Apple object wants to use Fruit's member functions
// it has to be declared in OOLUA_PROXY
OOLUA_PROXY(Apple, Fruit)
OOLUA_MFUNC(cleanApple)
OOLUA_SFUNC(anyCFunc)   //This function will not be exported and needs to be registered with OOLua see OOLUA::register_class_static
OOLUA_PROXY_END

#endif