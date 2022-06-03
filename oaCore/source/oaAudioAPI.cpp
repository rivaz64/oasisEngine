/**
* @file oaAudio.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 3/3/2022
*/

#include "oaAudioAPI.h"
#include "oaSound.h"

namespace oaEngineSDK{

SPtr<Sound>
AudioAPI::createSound()
{
  return makeSPtr<Sound>();
}

}

