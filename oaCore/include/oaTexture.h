/**
* @file oaTexture.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/7/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaBuffer.h"
#include "oaFlags.h"
#include "oaImage.h"

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
  FORMAT::E format;

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
  BIND::E bind;
};

/**
 * @brief the descriptor for the shader resourse of this texture
*/
struct ShaderResourseViewDesc{

  /**
   * @brief the format of the descriptor
  */
  FORMAT::E format;

  /**
   * @brief the dimencions of the descriptor
  */
  SRV_DIMENSION::E dimencion;

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
class OA_CORE_EXPORT Texture :
  public Resourse
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
   * @brief initializes a texture
   * @param size 
   * @param bind 
   * @param format 
   * @param data 
   * @param pitch 
   * @return 
  */
  virtual bool
  init(const Vector2I& size,BIND::E bind, FORMAT::E format,const void* data = nullptr, uint32 pitch = 0);

  /**
   * @brief initializes the texture from an image
   * @param image 
  */
  void
  initFromImage(SPtr<Image> image);

  virtual bool
  createShaderResource(FORMAT::E format);

  virtual bool
  createRenderTarget(FORMAT::E format);

  virtual bool
  createDepthStencil(FORMAT::E format);

  //virtual void
  //initForDepthStencil(const Vector2U& size) {}
  //
  //virtual void
  //initForRenderTarget(const Vector2U& size) {}

  virtual void
  release(){}

  /**
   * @brief gets the unique id of this texture
   * @return 
  */
  virtual void*
  getId();

  FORCEINLINE const FORMAT::E&
  getFormat(){
    return m_format;
  }

  FORCEINLINE const SPtr<Image>&
  getImage(){
    return m_image;
  }

 protected:

  SPtr<Image> m_image;

  FORMAT::E m_format;

  friend class ResoureManager;

};

}


