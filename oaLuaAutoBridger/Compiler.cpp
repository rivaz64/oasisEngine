#include "Compiler.h"
#include "CompilerState.h"
#include "CSIsClass.h"
#include "CSIsForExport.h"
#include "CSRegister.h"
#include "CSNotPublic.h"
#include "CSPublic.h"
#include "CSConstructor.h"
#include "CSCodeBlock.h"
#include "CSNone.h"

using oaEngineSDK::makeSPtr;

Compiler::Compiler(fstream& mt,fstream& t,fstream& f) :
  metatables(mt), tables(t), functions(f)
{
  m_states.push_back(makeSPtr<CSIsClass>());
  m_states.push_back(makeSPtr<CSIsForExport>());
  m_states.push_back(makeSPtr<CSRegister>());
  m_states.push_back(makeSPtr<CSNotPublic>());
  m_states.push_back(makeSPtr<CSPublic>());
  m_states.push_back(makeSPtr<CSConstructor>());
  m_states.push_back(makeSPtr<CSCodeBlock>());
  m_states.push_back(makeSPtr<CSNone>());

  m_currentState = m_states[0];
}



void
Compiler::evaluateToken(String& token)
{
  if(debug){
    oaEngineSDK::print(m_currentState.lock()->m_name);
    oaEngineSDK::print(token);
  }
  m_currentState.lock()->evaluateToken(this,token);
}

void
Compiler::end()
{
  m_currentState.lock()->end(this);
}

void 
Compiler::setCurrentState(COMPILER_STATES::E newState)
{
  m_currentState = m_states[newState];
}

void 
Compiler::continueSearch()
{
  if(isPublic){
    setCurrentState(COMPILER_STATES::kPublic);
  }
  else{
    setCurrentState(COMPILER_STATES::kNotPublic);
  }
}