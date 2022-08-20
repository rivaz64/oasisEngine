#pragma once
#include "oaPrerequisitesCore.h"
#include "oaLuaMetatables.h"
#include "oaLuaTable.h"
class lua_State;
namespace oaEngineSDK{
FORCEINLINE void loadLuaOasisLib(lua_State *L)
{
LUA_CLASS_REGISTER(Actor);
LUA_CLASS_REGISTER(Vector2f);
} 
} 
