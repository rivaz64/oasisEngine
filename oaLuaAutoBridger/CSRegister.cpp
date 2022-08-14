#include "CSRegister.h"
#include "Compiler.h"

void 
CSRegister::evaluateToken(Compiler* compiler, String& token, fstream& luaFile)
{
  luaFile<<"LUA_REGISTER(token)"<<std::endl;
  compiler->setCurrentState(COMPILER_STATES::kIsForExport);
}
