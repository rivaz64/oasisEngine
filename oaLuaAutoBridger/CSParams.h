#pragma once
#include "CompilerState.h"

using oaEngineSDK::Vector;

class CSParams :
  public CompilerState
{
 public:

  CSParams() :
    CompilerState("params") {}

  void
  evaluateToken(Compiler* compiler, String& token) override;

  bool forRegister = true;

  Vector<String> types;
};

