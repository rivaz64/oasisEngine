#pragma once

#include <oaPrerequisitesUtilities.h>
#include <oaStringUtilities.h>

using oaEngineSDK::fstream;
using oaEngineSDK::String;

class Compiler;

class CompilerState
{
 public:
  
  CompilerState(String&& name) :
    m_name(move(name)) {}

  virtual void
  evaluateToken(Compiler* compiler, String& token) = 0;

  virtual void
  end(Compiler* compiler);

  String m_name;
};

