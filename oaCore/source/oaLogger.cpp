/**
* @file oaLogger.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 1/21/2022
*/

#include "oaLogger.h"
#include "oaPath.h"
#include "oaTime.h"

namespace oaEngineSDK{

void Logger::log(const String& message,LOGGER_CHANNEL::E channel)
{
  print(message);
  m_allLogs.push_back({message,channel});
}

void Logger::clear(LOGGER_CHANNEL::E channel)
{
  Vector<LogEntry> entries;

  for(auto& message :m_allLogs){

    if(message.channel & channel){
      continue;
    }

    entries.push_back(message);
  }
  m_allLogs = entries;
}

void Logger::flush()
{
  Path path;

  FStream f;

  path.setCompletePath("Logs/log "+StringUtilities::intToString(Time::instance().getTime())+".txt");

  f.open(path.getCompletePath());

  for(auto& message :m_allLogs){
    String sChannel;

    switch(message.channel){

    case LOGGER_CHANNEL::DEBUG:
      sChannel = "[DEBUG]";
      break;

    case LOGGER_CHANNEL::WARNING:
      sChannel = "[WARNING]";
      break;

    case LOGGER_CHANNEL::ERRORCODE:
      sChannel = "[ERROR]";
      break;

    }
    
    f<<sChannel<<" "<<message.channel;
  }
  f.close();
}



}

