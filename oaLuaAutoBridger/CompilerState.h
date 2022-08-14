#pragma once

#include <oaPrerequisitesUtilities.h>
#include <oaStringUtilities.h>

using oaEngineSDK::fstream;
using oaEngineSDK::String;

class Compiler;

class CompilerState
{
 public:
  
  virtual void
  evaluateToken(Compiler* compiler, String& token, fstream& luaFile) = 0;
};

