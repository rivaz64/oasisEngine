#include "CSCodeBlock.h"
#include "Compiler.h"

void
CSCodeBlock::evaluateToken(Compiler* compiler, String& token)
{
  if(token == "}"){
    if(brackets == 1){
      compiler->continueSearch();
    }
    else{
      --brackets;
    }
  }
  else if(token == "{"){
    ++brackets;
  }
}
