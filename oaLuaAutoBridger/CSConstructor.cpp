#include "CSConstructor.h"
#include "Compiler.h"

void 
CSConstructor::evaluateToken(Compiler* compiler, String& token)
{
  if(token == "{"){
    compiler->setCurrentState(COMPILER_STATES::kCodeBlock);
  }
  if(token == "default;"){
    compiler->continueSearch();
  } 
}
