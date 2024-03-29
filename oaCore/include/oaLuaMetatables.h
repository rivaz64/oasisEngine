#include "oaLuaFunctions.h" 
namespace oaEngineSDK { 
LUA_METATABLE_REGISTER(Actor)
LUA_REGISTER_MEMBER(Actor,save)
LUA_REGISTER_MEMBER(Actor,load)
LUA_REGISTER_MEMBER(Actor,attach)
LUA_REGISTER_MEMBER(Actor,attachComponent)
LUA_REGISTER_MEMBER(Actor,update)
LUA_REGISTER_MEMBER(Actor,GetActorTransform)
LUA_REGISTER_MEMBER(Actor,getChilds)
LUA_REGISTER_MEMBER(Actor,getGlobalTransform)
LUA_CLOSE_REGISTER()
LUA_METATABLE_REGISTER(Vector2f)
LUA_REGISTER_MEMBER(Vector2f,magnitud)
LUA_REGISTER_MEMBER(Vector2f,normalized)
LUA_REGISTER_MEMBER(Vector2f,normalize)
LUA_REGISTER_MEMBER(Vector2f,project)
LUA_REGISTER_MEMBER(Vector2f,getDirection)
LUA_REGISTER_MEMBER(Vector2f,setDirection)
LUA_REGISTER_MEMBER(Vector2f,floor)
LUA_REGISTER_MEMBER(Vector2f,fraction)
LUA_REGISTER_MEMBER(Vector2f, get_x)
LUA_REGISTER_MEMBER(Vector2f, set_x)
LUA_REGISTER_MEMBER(Vector2f, get_y)
LUA_REGISTER_MEMBER(Vector2f, set_y)
LUA_CLOSE_REGISTER()
} 
