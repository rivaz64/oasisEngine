#pragma once

#pragma once
#include "CompilerState.h"

class CSRegister :
  public CompilerState
{ 
 public:

  CSRegister() :
    CompilerState("register") {}

  void
  evaluateToken(Compiler* compiler, String& token) override;
};


