/**
* @file oaFM_Sound.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 3/3/2022
*/

#pragma once
#include <oaSound.h>

#ifndef _AUDIO_ENGINE_H_
#define _AUDIO_ENGINE_H_

#include "fmod_studio.hpp"
#include "fmod.hpp"

#endif

namespace oaEngineSDK{

using FmodSound = FMOD::Sound;

class FM_Sound :
  public Sound
{

 public:

  ~FM_Sound();

  bool
  loadFromFile(const Path& path) override;

  void
  unload() override;
  
 private:

  FmodSound* sound;

  friend class FM_Audio;
};

}


