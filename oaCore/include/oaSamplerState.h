/**
* @file oaSamplerState.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/9/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaFlags.h"

namespace oaEngineSDK {

struct SamplerDesc {
  FILTER filter;
  TEXTURE_ADDRESS_MODE addressU;
  TEXTURE_ADDRESS_MODE addressV;
  TEXTURE_ADDRESS_MODE addressW;
  COMPARISON_FUNC comparison;
  float minLOD;
  float maxLOD;
};

class SamplerState
{
public:

  virtual ~SamplerState() {}

  /**
   * @brief describes the sampler state
   * @param  
   * @return 
  */
  virtual bool
  init(SamplerDesc /*descriptor*/) { return true; }
};

}


