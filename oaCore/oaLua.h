#pragma once
#include "oaPrerequisitesCore.h"
#include "oaLuaMetatables.h"
class lua_State;
FORCEINLINE void oaEngineSDK::loadLuaOasisLib(lua_State *L)
{
luaL_newlib(L, Actor_metatable);
luaL_newlib(L, Vector2f_metatable);
} 
