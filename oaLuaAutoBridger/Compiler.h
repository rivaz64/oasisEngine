#pragma once

#include <oaPrerequisitesUtilities.h>
#include <oaStringUtilities.h>

using oaEngineSDK::fstream;
using oaEngineSDK::String;
using oaEngineSDK::Vector;
using oaEngineSDK::SPtr;
using oaEngineSDK::WPtr;
using oaEngineSDK::int32;
using oaEngineSDK::ofstream;

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
kParams,
kNone
};
}

class Compiler
{
 public:
  
  Compiler(ofstream& mt,ofstream& t,ofstream& f,ofstream& fd,ofstream& i,ofstream& l);

  void
  evaluateToken(String& token);

  void
  end();

  void
  setCurrentState(COMPILER_STATES::E newState);

  void
  continueSearch();

  String className;
  String memberName;

  bool isPublic = false;
  bool isStatic = false;
  String type = "else";

  bool debug = false;

  ofstream& metatables;
  ofstream& tables;
  ofstream& functions;
  ofstream& fDefinitions;
  ofstream& includes;
  ofstream& libs;
 private:

  Vector<SPtr<CompilerState>> m_states;

  WPtr<CompilerState> m_currentState;
};

