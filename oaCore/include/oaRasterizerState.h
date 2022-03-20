/**
* @file oaRasterizer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/25/2022
*/

#pragma once

#include "oaPrerequisitesCore.h"

namespace oaEngineSDK{

namespace CULLING{
enum E{
  kNone=0,
  kFront,
  kBack
};
}

namespace FILL_MODE{
enum E{
  kSolid=0,
  kWireFrame
};
}

class OA_CORE_EXPORT RasterizerState
{
 public:
  
  virtual bool 
  init(CULLING::E culling, FILL_MODE::E fillMode);
};

}


