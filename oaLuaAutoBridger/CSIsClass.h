#pragma once
#include "CompilerState.h"

class CSIsClass :
  public CompilerState
{
 public:

  void
  evaluateToken(Compiler* compiler, String& token, fstream& luaFile) override;

};

