/**
* @file oaLogger.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 1/21/2021
*/

#define OA_LOG(s,...) Logger::instance().log( s,##__VA_ARGS__,__FILE__,__LINE__,__PRETTY_FUNCTION__ );

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

  template<class... Args>
  void log(String s,Args... args){
    m.lock();
    printf((s+" at file: %s in line %i at function %s").c_str(),args...);
    m.unlock();
  }

 private:
  
  String completeMessage;

  mutex m;
};

}
