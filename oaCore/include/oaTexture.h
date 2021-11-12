/**
* @file oaTexture.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/7/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaBuffer.h"
#include "oaFlags.h"

namespace oaEngineSDK{

struct TextureDesc{
  uint32 width;
  uint32 height;
  uint32 mipLevels;
  uint32 arraySize;
  FORMAT format;
  uint32 sampleCount;
  uint32 sampleQuality;
  BIND bind;
};

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

  virtual
  ~Texture() = default;

 public:
  /**
   * @brief loads the texture from a file
   * @param file 
   * @return 
  */
  virtual bool
  loadFromFile(const String& /*file*/) { return false; }

  virtual bool
  init(TextureDesc description) {return true;}

  friend class ResoureManager;

};

}


