#pragma once
#include "CompilerState.h"
class CSNone :
    public CompilerState
{
 public:
  void
  evaluateToken(Compiler* compiler, String& token, fstream& luaFile){}
};

