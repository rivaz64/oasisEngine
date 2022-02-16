/**
* @file oaScene.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"

namespace oaEngineSDK{

class Scene
{
  SPtr<Actor> m_root;
  friend class TestApp;
  friend class BaseApp;
};

}


