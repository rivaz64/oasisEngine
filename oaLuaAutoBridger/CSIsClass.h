#pragma once
#include "CompilerState.h"

class CSIsClass :
  public CompilerState
{
 public:

  CSIsClass() :
    CompilerState("is class") {}

  void
  evaluateToken(Compiler* compiler, String& token) override;

  void
  end(Compiler* compiler) override {}

};

