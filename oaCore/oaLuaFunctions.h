#include "oaLuaMacros.h" 
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}
namespace oaEngineSDK { 
int LUA_FUNCTION(Actor,save);
int LUA_FUNCTION(Actor,load);
int LUA_FUNCTION(Actor,attach);
int LUA_FUNCTION(Actor,attachComponent);
int LUA_FUNCTION(Actor,update);
int LUA_FUNCTION(Actor,GetActorTransform);
int LUA_FUNCTION(Actor,getChilds);
int LUA_FUNCTION(Actor,getGlobalTransform);
int LUA_FUNCTION(Vector2f,magnitud);
int LUA_FUNCTION(Vector2f,normalized);
int LUA_FUNCTION(Vector2f,normalize);
int LUA_FUNCTION(Vector2f,project);
int LUA_FUNCTION(Vector2f,getDirection);
int LUA_FUNCTION(Vector2f,setDirection);
int LUA_FUNCTION(Vector2f,floor);
int LUA_FUNCTION(Vector2f,fraction);
int LUA_FUNCTION(Vector2f,dot);
int LUA_FUNCTION(Vector2f,interpolate);
} 
