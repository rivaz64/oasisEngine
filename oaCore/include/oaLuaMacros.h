#pragma once
#define LUA_METATABLE_REGISTER(luaClass) static luaL_Reg luaClass##_metatable[] = {

#define LUA_TABLE_REGISTER(luaClass) static luaL_Reg luaClass##_table[] = {

#define LUA_MEMBER(luaClass,luaFunction) luaClass##_##luaFunction

#define LUA_FUNCTION(luaClass,luaFunction) LUA_MEMBER(luaClass,luaFunction) (lua_State* L)

#define LUA_DEFINITION(luaClass,luaFunction) LuaFunctions::##luaClass##_##luaFunction (lua_State* L)

#define LUA_REGISTER_MEMBER(luaClass,luaFunction) { #luaFunction, LUA_MEMBER(luaClass,luaFunction) },

#define LUA_CLOSE_REGISTER() { NULL, NULL } };

#define LUA_ASSERT_ARGS_NUM(x) OA_ASSERT(lua_gettop(L) != x)

#define checkint luaL_checkinteger
#define checkint32 luaL_checkinteger
#define checkuint32 luaL_checkinteger
#define checkstring luaL_checkstring
#define checkfloat luaL_checknumber

#define LUA_CHECK_PARAM(ty,x) ty var##x = check##ty##(L,x);

#define LUA_CHECK_USER_PARAM(ty,x) ty* var##x = reinterpret_cast<ty*>(luaL_checkudata(L,x,#ty));

#define pushbool lua_pushboolean 
#define pushint lua_pushinteger
#define pushint32 lua_pushinteger
#define pushuint32 lua_pushinteger
#define pushfloat lua_pushnumber
#define pushString lua_pushstring

#define LUA_PUSH_PARAM(ty,x) push##ty##(L,x);

#define LUA_PUSH_USER_PARAM(x) lua_pushlightuserdata(L,&x);

//LUA_CONSTRUCTOR
#define TO_STRING(x) #x

#define LUA_CONSTRUCTOR(luaClass)\
static int LUA_FUNCTION( luaClass ,new){\
lua_remove(L, 1);\
*static_cast<##luaClass##**>(lua_newuserdata(L, sizeof(void*))) = new luaClass();\
luaL_setmetatable(L, TO_STRING( luaClass##_metatable ));\
return 1;\
};

#define LUA_GETTER(luaClass,luaAtribute) luaClass##_get_##luaAtribute
#define LUA_SETTER(luaClass,luaAtribute) luaClass##_set_##luaAtribute

#define LUA_GET_ATRIBUTE(luaClass,luaAtribute,returnType)\
static int luaClass##_get_##luaAtribute##(lua_State* L) {\
LUA_CHECK_USER_PARAM( luaClass ,1)\
auto ret = var1->##luaAtribute;\
returnType;\
return 1;};

#define LUA_SET_ATRIBUTE(luaClass,luaAtribute,check)\
static int luaClass##_set_##luaAtribute##(lua_State* L) {\
LUA_CHECK_USER_PARAM( luaClass ,1)\
check;\
var1->##luaAtribute = var2;\
return 0;};

#define LUA_CLASS_REGISTER(luaClass)\
lua_register(L,#luaClass,luaClass##_new);\
luaL_newmetatable(L, #luaClass );\
luaL_setfuncs(L, luaClass##_metatable , 0);\
lua_pop(L,1);

