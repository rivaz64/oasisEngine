#include "Compiler.h"
#include "CompilerState.h"
#include "CSIsClass.h"
#include "CSIsForExport.h"
#include "CSRegister.h"
#include "CSNone.h"

using oaEngineSDK::makeSPtr;

Compiler::Compiler()
{
  m_states.push_back(makeSPtr<CSIsClass>());
  m_states.push_back(makeSPtr<CSIsForExport>());
  m_states.push_back(makeSPtr<CSRegister>());
  m_states.push_back(makeSPtr<CSNone>());

  m_currentState = m_states[0];
}

void
Compiler::evaluateToken(String& token, fstream& luaFile)
{
  m_currentState.lock()->evaluateToken(this,token,luaFile);
}

void 
Compiler::setCurrentState(COMPILER_STATES::E newState)
{
  m_currentState = m_states[newState];
}

