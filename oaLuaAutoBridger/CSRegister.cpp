#include "CSRegister.h"
#include "Compiler.h"

void 
CSRegister::evaluateToken(Compiler* compiler, String& token, fstream& luaFile)
{
  luaFile<<"LUA_REGISTER_CLASS("<<token<<")"<<std::endl;
  compiler->className = token;
  compiler->setCurrentState(COMPILER_STATES::kNotPublic);
}
