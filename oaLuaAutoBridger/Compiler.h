#pragma once

#include <oaPrerequisitesUtilities.h>
#include <oaStringUtilities.h>

using oaEngineSDK::fstream;
using oaEngineSDK::String;
using oaEngineSDK::Vector;
using oaEngineSDK::SPtr;
using oaEngineSDK::WPtr;
using oaEngineSDK::int32;

class CompilerState;

namespace COMPILER_STATES
{
enum E{
kIsClass = 0,
kIsForExport,
kRegister,
kNone
};
}

class Compiler
{
 public:
  
  Compiler();

  void
  evaluateToken(String& token, fstream& luaFile);

  void
  setCurrentState(COMPILER_STATES::E newState);

  String className;

 private:

  Vector<SPtr<CompilerState>> m_states;

  WPtr<CompilerState> m_currentState;
};

