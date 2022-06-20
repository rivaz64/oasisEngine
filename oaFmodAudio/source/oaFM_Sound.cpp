/**
* @file oaFM_Sound.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 3/3/2022
*/

#include "oaFM_Sound.h"
#include "oaFM_Audio.h"

namespace oaEngineSDK{

FM_Sound::~FM_Sound()
{
  unload();
}

bool
FM_Sound::loadFromFile(const Path& path)
{
  auto& audioSystem = reinterpret_cast<FM_Audio*>(FM_Audio::instancePtr())->m_audioSystem;
  auto wPath = path.getCompletePath();
  auto sPath = StringUtilities::toString(wPath);
  auto result = audioSystem->createSound(sPath.c_str(),FMOD_DEFAULT,0,&sound);

  if(result == FMOD_OK){
    return true;
  }
  return false;
}

void 
FM_Sound::unload()
{
  sound->release();
  sound = 0;
}

}
