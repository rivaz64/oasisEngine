/**
* @file oaSamplerState.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/9/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaFlags.h"

namespace oaEngineSDK {

/**
 * @brief the descriptor for the sampler
*/
struct SamplerDesc {
  /**
   * @brief how it is going to filter
  */
  FILTER::E filter;

  /**
   * @brief who it handles the execes in u
  */
  TEXTURE_ADDRESS_MODE::E addressU;

  /**
   * @brief who it handles the execes in v
  */
  TEXTURE_ADDRESS_MODE::E addressV;

  /**
   * @brief who it handles the execes in w
  */
  TEXTURE_ADDRESS_MODE::E addressW;

  /**
   * @brief the funcion for comparicion
  */
  COMPARISON_FUNC::E comparison;

  /**
   * @brief the minimum number of LODs
  */
  float minLOD;

  /**
   * @brief the maximum number of LODs
  */
  float maxLOD;
};

/**
 * @brief the state for the sampler for textures
*/
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


