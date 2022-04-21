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
  init(TEXTURE_ADDRESS_MODE::E textureAdressMode) { return true; }
};

}


