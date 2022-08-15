#include "CSRegister.h"
#include "Compiler.h"

void 
CSRegister::evaluateToken(Compiler* compiler, String& token)
{
  compiler->metatables<<"LUA_METATABLE_REGISTER("<<token<<")"<<std::endl;
  compiler->tables<<"LUA_TABLE_REGISTER("<<token<<")"<<std::endl;
  compiler->className = token;
  compiler->setCurrentState(COMPILER_STATES::kNotPublic);
}
