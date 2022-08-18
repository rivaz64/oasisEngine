#include "oaLua.h"
#include "oaLuaMetatables.h"
void oaEngineSDK::loadLuaOasisLib(lua_State *L)
{
luaL_newlib(L, Actor_metatable);
luaL_newlib(L, Vector2f_metatable);
} 
