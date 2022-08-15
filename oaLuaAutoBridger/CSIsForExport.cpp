#include "CSIsForExport.h"
#include "Compiler.h"

void 
CSIsForExport::evaluateToken(Compiler* compiler, String& token)
{
  if(token == "LUAEXPORT"){
    compiler->setCurrentState(COMPILER_STATES::kRegister);
  }
}
