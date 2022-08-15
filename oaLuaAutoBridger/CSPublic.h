#pragma once
#include "CompilerState.h"
class CSPublic :
  public CompilerState
{
 public:

  CSPublic() :
    CompilerState("public") {}

  void
  evaluateToken(Compiler* compiler, String& token) override;

  bool isStatic = false;
};

