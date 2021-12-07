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

/**
 * @brief the descriptor for the texture
*/
struct TextureDesc{

  /**
   * @brief the width of the texture
  */
  uint32 width;

  /**
   * @brief the height of the texture
  */
  uint32 height;

  /**
   * @brief the number of mipmaps
  */
  uint32 mipLevels;

  /**
   * @brief the number of the texutres
  */
  uint32 arraySize;
  FORMAT format;
  uint32 sampleCount;
  uint32 sampleQuality;
  BIND bind;
};

struct ShaderResourseViewDesc{
  FORMAT format;
  SRV_DIMENSION dimencion;
  uint32 mostDetailedMip;
  uint32 mipLevels;
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

  /**
   * @brief initalizes only the texture
   * @param description 
   * @return 
  */
  virtual bool
  init(TextureDesc /*description*/) {return true;}

  /**
   * @brief initlializes everything needed for the texture
   * @param description the description for the texture
   * @param descriptionSRV the description for the shader resourse
   * @return 
  */
  virtual bool
  init(TextureDesc /*description*/,ShaderResourseViewDesc /*descriptionSRV*/ ) {return true;}

  friend class ResoureManager;

};

}


