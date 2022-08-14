#pragma once
#include "CompilerState.h"
class CSIsForExport :
  public CompilerState
{ 
 public:

  CSIsForExport() :
    CompilerState("is for export") {}

  void
  evaluateToken(Compiler* compiler, String& token, fstream& luaFile) override;

  void
  end(fstream& luaFile) override {}
};

