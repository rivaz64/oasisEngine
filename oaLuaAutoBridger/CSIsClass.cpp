#include "CSIsClass.h"
#include "Compiler.h"

void 
CSIsClass::evaluateToken(Compiler* compiler, String& token, fstream& luaFile)
{
  if(token == "class"){
    compiler->setCurrentState(COMPILER_STATES::kIsForExport);
  }
}
