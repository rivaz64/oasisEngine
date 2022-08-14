#pragma once
#include "CompilerState.h"

class CSNotPublic :
  public CompilerState
{
 public:

  CSNotPublic() :
    CompilerState("not public") {}

  void
  evaluateToken(Compiler* compiler, String& token, fstream& luaFile) override;
};

