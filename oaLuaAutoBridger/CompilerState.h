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
  evaluateToken(Compiler* compiler, String& token, fstream& luaFile) = 0;

  virtual void
  end(fstream& luaFile);

  String m_name;
};

