#pragma once
#define LUA_METATABLE_REGISTER(luaClass) static luaL_Reg luaClass##_metatable[] = {

#define LUA_TABLE_REGISTER(luaClass) static luaL_Reg luaClass##_table[] = {

#define LUA_MEMBER(luaClass,luaFunction) luaClass##_##luaFunction

#define LUA_FUNCTION(luaClass,luaFunction) LUA_MEMBER(luaClass,luaFunction) (lua_State* L)

#define LUA_REGISTER_MEMBER(luaClass,luaFunction) { #luaFunction, LUA_MEMBER(luaClass,luaFunction) },

#define LUA_CLOSE_REGISTER() { NULL, NULL } };
