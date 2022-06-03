/**
* @file oaAudio.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 3/3/2022
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include <oaModule.h>

namespace oaEngineSDK{

/**
 * @brief the api dor the audio plugin
*/
class OA_CORE_EXPORT AudioAPI :
  public Module<AudioAPI>
{
 public:
  
  virtual SPtr<Sound>
  createSound();

  virtual void
  playSound(SPtr<Sound> sound) {}

 private:

  friend class Module<AudioAPI>;
};

}


