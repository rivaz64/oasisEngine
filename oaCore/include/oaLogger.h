/**
* @file oaLogger.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 1/21/2022
*/

#define OA_LOG(message) Logger::instance().log(message+" at file: "+__FILE__+" in line "+toString(__LINE__) + " at function "+__PRETTY_FUNCTION__);

#pragma once

#include "oaPrerequisitesCore.h"
#include <oaModule.h>

namespace oaEngineSDK{

class OA_CORE_EXPORT Logger :
  public Module<Logger>
{
 public:

  void
  onStartUp() override;

  void
  onShutDown() override;

  void 
  log(const String& message);

 private:
  
  void 
  flush();

  Vector<String> m_completeMessage;

  friend class BaseApp;
};

}
