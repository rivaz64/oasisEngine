/**
* @file oaLogger.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 1/21/2022
*/

#include "oaLogger.h"
#include "oaFile.h"
#include "oaPath.h"
#include "oaTime.h"

using std::cout;

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

void Logger::log(const String& message, const String& file, uint32 line, const String& function)
{
  completeMessage += message+" at file: "+file+" in line "+std::to_string(line) + " at function "+function+'\n';
}

void Logger::flush()
{
  if(flushed){
    return;
  }
  Path path;
  File f;
  path.setCompletePath("Logs/log "+std::to_string(Time::instance().getTime())+".txt");
  f.open(path,FILEFLAGS::WRITE);
  f.write(completeMessage);
  f.close();
  flushed = true;
}


/*
void
Logger::logToConsole(String message)
{
  cout<<message+'\n';
  //completeMessage += message+'\n';
}*/

}

