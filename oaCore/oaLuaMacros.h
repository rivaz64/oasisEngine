#pragma once
#define LUA_REGISTER_CLASS(luaClass) static luaL_Reg ##luaClass##_metatable[] = {
//luaL_newmetatable(L, #luaClass);

#define LUA_REGISTER_MEMBER(luaClass,luaFunction) { #luaFunction, ##luaClass##_##luaFunction## },

#define LUA_CLOSE_REGISTER() { NULL, NULL } };
