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

  /**
   * @brief the format
  */
  FORMAT format;

  /**
   * @brief the number of samples
  */
  uint32 sampleCount;

  /**
   * @brief the quality
  */
  uint32 sampleQuality;

  /**
   * @brief the binding flag
  */
  BIND bind;
};

/**
 * @brief the descriptor for the shader resourse of this texture
*/
struct ShaderResourseViewDesc{

  /**
   * @brief the format of the descriptor
  */
  FORMAT format;

  /**
   * @brief the dimencions of the descriptor
  */
  SRV_DIMENSION dimencion;

  /**
   * @brief the  mips
  */
  uint32 mostDetailedMip;

  /**
   * @brief the number of mip levels
  */
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

  /**
   * @brief gets the unique id of this texture
   * @return 
  */
  virtual void*
  getId() {return 0;}

  friend class ResoureManager;

};

}


