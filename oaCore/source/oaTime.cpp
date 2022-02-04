/**
* @file oaTime.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 12/3/2021
*/

#include "oaTime.h"
#include <ctime>
#include <ratio>
#include <chrono>
#include <ratio>


using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;
namespace oaEngineSDK{
String 
Time::getActualDateAndTime()
{
  static auto now = system_clock::now();
  std::time_t time = system_clock::to_time_t(now);
  char mbstr[124];
  std::strftime(mbstr, 100, "%d/%m/%Y %T", std::localtime(&time));
  return mbstr;
}
uint32 
Time::getTime()
{
  auto start = high_resolution_clock::now();
  uint32 id = static_cast<uint32>(duration_cast<seconds>(start.time_since_epoch()).count());
  return id;
}
void Time::update()
{
  static auto start = high_resolution_clock::now();

  static auto end = high_resolution_clock::now();

  end = high_resolution_clock::now();

  m_deltaTime = duration<float>(end - start).count();

  start = high_resolution_clock::now();
}

}

