/**
* @file oaTime.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 12/3/2021
*/

#include "oaTime.h"
#include <ctime>
#include <ratio>
#include <chrono>

namespace oaEngineSDK{

void Time::update()
{
  static auto start = std::chrono::high_resolution_clock::now();

  static auto end = std::chrono::high_resolution_clock::now();

  end = std::chrono::high_resolution_clock::now();

  deltaTime = std::chrono::duration<float>(end - start).count();

  start = std::chrono::high_resolution_clock::now();
}

}

