#include "CompilerState.h"
#include "Compiler.h"

void
CompilerState::end(Compiler* compiler)
{
  compiler->metatables<<"LUA_CLOSE_REGISTER()"<<std::endl;
  compiler->tables<<"LUA_CLOSE_REGISTER()"<<std::endl;
}
