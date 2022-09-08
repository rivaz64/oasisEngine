/**
* @file oaFM_Audio.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 3/3/2022
*/

#include "oaFM_Audio.h"
#include "oaFM_Sound.h"
//#include "common.h"

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
  FMOD::Debug_Initialize(FMOD_DEBUG_LEVEL_LOG);
  //Common_Init(&m_extradriverdata);
  result = System_Create(&m_audioSystem);
  result = m_audioSystem->init(3,FMOD_INIT_NORMAL,nullptr);
  result = m_audioSystem->setDriver(0);
  //ERRCHECK(result);
  //bool check = audioSystem->
  //AudioStudioSystem::create(&audioStudioSystem);

}

SPtr<Sound>
FM_Audio::createSound()
{
  //audioSystem->createSound()
  return makeSPtr<FM_Sound>();
}

void 
FM_Audio::playSound(WPtr<Sound> wSound)
{
  auto sound = wSound.lock();
  auto fModSound = cast<FM_Sound>(sound);
  Channel* channel = nullptr;
  m_audioSystem->playSound(fModSound->sound,nullptr,false,&channel);
}

}

