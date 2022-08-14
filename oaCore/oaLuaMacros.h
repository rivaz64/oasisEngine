#pragma once
#define LUA_REGISTER(luaClass) luaL_newmetatable(L, #luaClass);