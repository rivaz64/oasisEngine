#include "oaLuaFunctions.h" 
namespace oaEngineSDK { 
LUA_TABLE_REGISTER(Actor)
LUA_REGISTER_MEMBER(Actor,new)
LUA_CLOSE_REGISTER()
LUA_TABLE_REGISTER(Vector2f)
//LUA_REGISTER_MEMBER(Vector2f,new)
{"new",Vector2f_new},
LUA_REGISTER_MEMBER(Vector2f,dot)
LUA_REGISTER_MEMBER(Vector2f,interpolate)
LUA_CLOSE_REGISTER()
} 
