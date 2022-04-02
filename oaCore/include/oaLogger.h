/**
* @file oaLogger.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 1/21/2022
*/

#define OA_DEBUG_LOG(message) Logger::instance().log(String(message)+" at file: "+__FILE__+" in line "+StringUtilities::intToString(__LINE__) + " at function "+__PRETTY_FUNCTION__,LOGGER_CHANNEL::DEBUG);

#define OA_WARNING_LOG(message) Logger::instance().log(String(message)+" at file: "+__FILE__+" in line "+toString(__LINE__) + " at function "+__PRETTY_FUNCTION__,LOGGER_CHANNEL::WARNING);

#define OA_ERROR_LOG(message) Logger::instance().log(String(message)+" at file: "+__FILE__+" in line "+toString(__LINE__) + " at function "+__PRETTY_FUNCTION__,LOGGER_CHANNEL::ERRORCODE);

#pragma once

#include "oaPrerequisitesCore.h"
#include <oaModule.h>

namespace oaEngineSDK{



namespace LOGGER_CHANNEL{
  enum E{
    DEBUG = 0,
    WARNING,
    ERRORCODE
  };
}

struct LogEntry{

  LogEntry(const String& message,LOGGER_CHANNEL::E channel) :
    message(message),channel(channel){}

  String message;
  LOGGER_CHANNEL::E channel;


};

class OA_CORE_EXPORT Logger :
  public Module<Logger>
{
 public:

  /**
   * @brief 
   * @param message the message to log
   * @param channel the channel of this log
  */
  void 
  log(const String& message,LOGGER_CHANNEL::E channel);

  /**
   * @brief clears all the logs of cretain channels
   * @param channel 
  */
  void
  clear(LOGGER_CHANNEL::E channel);

 private:
  
  void 
  flush();

  Vector<LogEntry> m_allLogs;

  friend class BaseApp;
};

}
