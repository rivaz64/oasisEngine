#include "CSNotPublic.h"
#include "Compiler.h"

void
CSNotPublic::evaluateToken(Compiler* compiler, String& token, fstream& luaFile)
{
  if(token == "public:"){
    compiler->isPublic = true;
    compiler->setCurrentState(COMPILER_STATES::kPublic);
  }
}
