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
class OA_CORE_EXPORT Audio :
  public Module<Audio>
{
 public:
  
  virtual SPtr<Sound>
  createSound();

  virtual void
  loadAudio(const Path& file){}

 private:
  friend class Module<Audio>;
};

}


