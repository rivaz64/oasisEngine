#include "CompilerState.h"

void
CompilerState::end(fstream& luaFile)
{
  luaFile<<"LUA_CLOSE_REGISTER()"<<std::endl;
}
