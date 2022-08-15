#include "CSNotPublic.h"
#include "Compiler.h"

void
CSNotPublic::evaluateToken(Compiler* compiler, String& token)
{
  if(token == "public:"){
    compiler->isPublic = true;
    compiler->setCurrentState(COMPILER_STATES::kPublic);
  }
}
