/**
* @file oaScene.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"

namespace oaEngineSDK{

class OA_CORE_EXPORT Scene
{
 public:

  void
  init();

  FORCEINLINE SPtr<Actor> 
  getRoot(){
    return m_root;
  }

 private:

  SPtr<Actor> m_root;

};

}


