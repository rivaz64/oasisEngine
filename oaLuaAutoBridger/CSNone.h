#pragma once
#include "CompilerState.h"
class CSNone :
    public CompilerState
{
 public:

  CSNone() :
    CompilerState("none") {}

  void
  evaluateToken(Compiler* compiler, String& token){}
};

