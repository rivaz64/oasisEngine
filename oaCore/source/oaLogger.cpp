/**
* @file oaLogger.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 1/21/2022
*/

#include "oaLogger.h"
#include "oaPath.h"
#include "oaTime.h"

namespace oaEngineSDK{

void 
Logger::onStartUp()
{
  //outputFile.open("logger.txt");
}

void 
Logger::onShutDown()
{
  //outputFile << completeMessage;
  //outputFile.close();
  
}

void Logger::log(const String& message)
{
  m_completeMessage.push_back(message);
}

void Logger::flush()
{
  Path path;
  FStream f;
  path.setCompletePath("Logs/log "+toString(Time::instance().getTime())+".txt");
  f.open(path.getCompletePath());
  for(auto& message :m_completeMessage){
    f<<message;
  }
  f.close();
}



}

