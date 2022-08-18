#include "oaLuaMacros.h" 
#include "oaPrerequisitesCore.h" 
#include "oaLuaIncludes.h" 
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}
namespace oaEngineSDK { 
static int LUA_FUNCTION(Actor,save){
LUA_ASSERT_ARGS_NUM(2);
LUA_CHECK_USER_PARAM(Actor,1);
LUA_CHECK_USER_PARAM(Serializer,2);
var1->save(*var2);
return 0;
}
static int LUA_FUNCTION(Actor,load){
LUA_ASSERT_ARGS_NUM(2);
LUA_CHECK_USER_PARAM(Actor,1);
LUA_CHECK_USER_PARAM(Serializer,2);
var1->load(*var2);
return 0;
}
static int LUA_FUNCTION(Actor,attach){
LUA_ASSERT_ARGS_NUM(2);
LUA_CHECK_USER_PARAM(Actor,1);
LUA_CHECK_USER_PARAM(SPtr<Actor>,2);
var1->attach(*var2);
return 0;
}
static int LUA_FUNCTION(Actor,attachComponent){
LUA_ASSERT_ARGS_NUM(2);
LUA_CHECK_USER_PARAM(Actor,1);
LUA_CHECK_USER_PARAM(SPtr<Component>,2);
var1->attachComponent(*var2);
return 0;
}
static int LUA_FUNCTION(Actor,update){
LUA_ASSERT_ARGS_NUM(1);
LUA_CHECK_USER_PARAM(Actor,1);
var1->update();
return 0;
}
static int LUA_FUNCTION(Actor,GetActorTransform){
LUA_ASSERT_ARGS_NUM(1);
LUA_CHECK_USER_PARAM(Actor,1);
auto ret = var1->GetActorTransform();
LUA_PUSH_USER_PARAM(ret)
return 1;
}
static int LUA_FUNCTION(Actor,getChilds){
LUA_ASSERT_ARGS_NUM(1);
LUA_CHECK_USER_PARAM(Actor,1);
auto ret = var1->getChilds();
LUA_PUSH_USER_PARAM(ret)
return 1;
}
static int LUA_FUNCTION(Actor,getGlobalTransform){
LUA_ASSERT_ARGS_NUM(1);
LUA_CHECK_USER_PARAM(Actor,1);
auto ret = var1->getGlobalTransform();
LUA_PUSH_USER_PARAM(ret)
return 1;
}
static int LUA_FUNCTION(Vector2f,magnitud){
LUA_ASSERT_ARGS_NUM(1);
LUA_CHECK_USER_PARAM(Vector2f,1);
auto ret = var1->magnitud();
LUA_PUSH_PARAM(float,ret)
return 1;
}
static int LUA_FUNCTION(Vector2f,normalized){
LUA_ASSERT_ARGS_NUM(1);
LUA_CHECK_USER_PARAM(Vector2f,1);
auto ret = var1->normalized();
LUA_PUSH_USER_PARAM(ret)
return 1;
}
static int LUA_FUNCTION(Vector2f,normalize){
LUA_ASSERT_ARGS_NUM(1);
LUA_CHECK_USER_PARAM(Vector2f,1);
var1->normalize();
return 0;
}
static int LUA_FUNCTION(Vector2f,project){
LUA_ASSERT_ARGS_NUM(2);
LUA_CHECK_USER_PARAM(Vector2f,1);
LUA_CHECK_USER_PARAM(Vector2f,2);
auto ret = var1->project(*var2);
LUA_PUSH_USER_PARAM(ret)
return 1;
}
static int LUA_FUNCTION(Vector2f,getDirection){
LUA_ASSERT_ARGS_NUM(1);
LUA_CHECK_USER_PARAM(Vector2f,1);
auto ret = var1->getDirection();
LUA_PUSH_PARAM(float,ret)
return 1;
}
static int LUA_FUNCTION(Vector2f,setDirection){
LUA_ASSERT_ARGS_NUM(2);
LUA_CHECK_USER_PARAM(Vector2f,1);
LUA_CHECK_PARAM(float,2);
var1->setDirection(var2);
return 0;
}
static int LUA_FUNCTION(Vector2f,floor){
LUA_ASSERT_ARGS_NUM(1);
LUA_CHECK_USER_PARAM(Vector2f,1);
auto ret = var1->floor();
LUA_PUSH_USER_PARAM(ret)
return 1;
}
static int LUA_FUNCTION(Vector2f,fraction){
LUA_ASSERT_ARGS_NUM(1);
LUA_CHECK_USER_PARAM(Vector2f,1);
auto ret = var1->fraction();
LUA_PUSH_USER_PARAM(ret)
return 1;
}
static int LUA_FUNCTION(Vector2f,dot){
LUA_ASSERT_ARGS_NUM(2);
LUA_CHECK_USER_PARAM(Vector2f,1);
LUA_CHECK_USER_PARAM(Vector2f,2);
auto ret = Vector2f::dot(*var1,*var2);
LUA_PUSH_PARAM(float,ret)
return 1;
}
static int LUA_FUNCTION(Vector2f,interpolate){
LUA_ASSERT_ARGS_NUM(3);
LUA_CHECK_USER_PARAM(Vector2f,1);
LUA_CHECK_USER_PARAM(Vector2f,2);
LUA_CHECK_PARAM(float,3);
auto ret = Vector2f::interpolate(*var1,*var2,var3);
LUA_PUSH_USER_PARAM(ret)
return 1;
}
} 
