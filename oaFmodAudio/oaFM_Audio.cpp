/**
* @file oaFM_Audio.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 3/3/2022
*/

#include "oaFM_Audio.h"
#include <oaPath.h>
#include "oaFM_Sound.h"

namespace oaEngineSDK{

//void
//oaFM_Audio::loadAudio(const Path& path)
//{
//  auto wPath = path.getCompletePath();
//  auto sPath = StringUtilities::toString(wPath);
//  audioSystem->createSound()
//  //audioSystem->loadBankFile(sPath.c_str(),FMOD_STUDIO_LOAD_BANK_NORMAL,&audioBank);
//}

void 
FM_Audio::onStartUp()
{
  FMOD_RESULT result;
  
  result = System_Create(&audioSystem);
}

SPtr<Sound>
FM_Audio::createSound()
{
  return makeSPtr<FM_Sound>();
}

}

