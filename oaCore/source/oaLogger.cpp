/**
* @file oaLogger.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 1/21/2021
*/

#include "oaLogger.h"
#include <stdarg.h>
#include <iostream>

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

/*
void
Logger::logToConsole(String message)
{
  cout<<message+'\n';
  //completeMessage += message+'\n';
}*/

}

