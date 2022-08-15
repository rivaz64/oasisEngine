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
kNotPublic,
kPublic,
kConstructor,
kCodeBlock,
kNone
};
}

class Compiler
{
 public:
  
  Compiler(fstream& mt,fstream& t,fstream& f);

  void
  evaluateToken(String& token);

  void
  end();

  void
  setCurrentState(COMPILER_STATES::E newState);

  void
  continueSearch();

  String className;

  bool isPublic = false;

  bool debug = false;

  fstream& metatables;
  fstream& tables;
  fstream& functions;
 private:

  Vector<SPtr<CompilerState>> m_states;

  WPtr<CompilerState> m_currentState;
};

