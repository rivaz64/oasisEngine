/**
* @file oaFM_Audio.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 3/3/2022
*/

#pragma once

#include <oaAudio.h>
#include "oaFM_Sound.h"

#ifndef _AUDIO_ENGINE_H_
#define _AUDIO_ENGINE_H_

#include "fmod_studio.hpp"
#include "fmod.hpp"

#endif

namespace oaEngineSDK{

using AudioSystem = FMOD::System;
using AudioStudioSystem = FMOD::Studio::System;
using AudioBank = FMOD::Studio::Bank;
using FMOD::System_Create;

class FM_Audio :
  public Audio
{
 public:
  
  void
  onStartUp() override;

  SPtr<Sound>
  createSound() override;

  void
  loadAudio(const Path& file) override;

  

 private:
  
  AudioSystem* audioSystem;

  AudioStudioSystem* audioStudioSystem;

  AudioBank* audioBank;

};

}


