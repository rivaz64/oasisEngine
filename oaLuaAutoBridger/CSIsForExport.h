#pragma once
#include "CompilerState.h"
class CSIsForExport :
  public CompilerState
{ 
 public:

  void
  evaluateToken(Compiler* compiler, String& token, fstream& luaFile) override;
};

