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
  SPtr<Actor> m_root;

  friend class TestApp;
  friend class BaseApp;
};

}


