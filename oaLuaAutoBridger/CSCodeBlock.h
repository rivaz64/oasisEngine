#pragma once
#include "CompilerState.h"

using oaEngineSDK::uint32;

class CSCodeBlock :
  public CompilerState
{
 public:

  CSCodeBlock() :
    CompilerState("code block") {}

  void
  evaluateToken(Compiler* compiler, String& token, fstream& luaFile) override;

 private:
  uint32 brackets = 1;
};

