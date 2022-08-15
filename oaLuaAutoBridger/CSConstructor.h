#pragma once
#include "CompilerState.h"
class CSConstructor :
  public CompilerState
{
 public:
  
   CSConstructor() :
     CompilerState("constructor") {}
  void
  evaluateToken(Compiler* compiler, String& token) override;
};

