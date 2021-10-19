/**
* @file oaTexture.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/7/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"

namespace oaEngineSDK{

/**
 * @brief class for all kinds of textures
*/
class OA_CORE_EXPORT Texture
{
 public:

  /**
   * @brief default constructor for the texture
  */
  Texture() = default;

 protected:
  /**
   * @brief loads the texture from a file
   * @param file 
   * @return 
  */
  virtual bool
  loadFromFile(const String& file);

  friend class ResoureManager;

};

}


