#pragma once

#pragma once
#include "CompilerState.h"

class CSRegister :
  public CompilerState
{ 
 public:

  void
  evaluateToken(Compiler* compiler, String& token, fstream& luaFile) override;
};


