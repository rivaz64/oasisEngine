#pragma once
#include "CompilerState.h"

class CSIsClass :
  public CompilerState
{
 public:

  CSIsClass() :
    CompilerState("is class") {}

  void
  evaluateToken(Compiler* compiler, String& token, fstream& luaFile) override;

  void
  end(fstream& luaFile) override {}

};

