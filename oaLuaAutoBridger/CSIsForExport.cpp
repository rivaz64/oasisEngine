#include "CSIsForExport.h"
#include "Compiler.h"

void 
CSIsForExport::evaluateToken(Compiler* compiler, String& token, fstream& luaFile)
{
  if(token == "LUAEXPORT"){
    compiler->setCurrentState(COMPILER_STATES::kRegister);
  }
}
