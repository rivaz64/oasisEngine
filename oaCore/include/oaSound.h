/**
* @file oaSound.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 3/3/2022
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaResourse.h"

namespace oaEngineSDK{

/**
 * @brief can be reproduced to sound
*/
class OA_CORE_EXPORT Sound :
  public Resourse
{
 public:

  RESOURSE_TYPE::E
  getType() override
  {
    return RESOURSE_TYPE::kSound;
  }

  virtual bool
  loadFromFile(const Path& path);

  virtual void
  unload() {}

};

}


