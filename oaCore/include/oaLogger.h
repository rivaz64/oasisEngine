/**
* @file oaLogger.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 1/21/2022
*/

#define OA_LOG(s) Logger::instance().log( s,__FILE__,__LINE__,__PRETTY_FUNCTION__ );

#pragma once

#include "oaPrerequisitesCore.h"
#include <oaModule.h>
#include <stdio.h>
#include <mutex>

using std::mutex;

namespace oaEngineSDK{

class OA_CORE_EXPORT Logger :
  public Module<Logger>
{
 public:

  void
  onStartUp() override;

  void
  onShutDown() override;

  void log(const String& message,const String& file,uint32 line,const String& function);
    //printf((s+" at file: %s in line %i at function %s").c_str(),args...);
  
  void 
  flush();

 private:
  
  String completeMessage;

  mutex m;

  bool flushed = false;
};

}
