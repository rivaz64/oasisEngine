/**
* @file oaImage.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/12/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaResourse.h"
#include "oaFlags.h"
#include "oaVector2I.h"

namespace oaEngineSDK{

class Image :
  public Resourse
{
 public:

  Image() = default;

  Image(const Vector2I& size, int32 bitsPerPixel,FORMAT::E format) :
    m_size(size), m_bitsPerPixel(bitsPerPixel), m_format(format) 
  {
    init();
  }

  FORCEINLINE void
  init(){
     m_pixels.resize(getNumberOfBytes());
  }

  FORCEINLINE int32
  getPitch(){
    return (m_size.x*m_bitsPerPixel)/8;
  }

  FORCEINLINE int32
  getBitsPerPixel(){
    return m_bitsPerPixel;
  }

  FORCEINLINE float
  getBytesPerPixel(){
    return static_cast<float>(m_bitsPerPixel)/8.f;
  }

  FORCEINLINE int32
  getNumberOfBytes(){
    return (m_size.x*m_size.y)*getBytesPerPixel();
  }

  FORCEINLINE FORMAT::E
  getFormat(){
    return m_format;
  }

  FORCEINLINE const Vector2I&
  getSize(){
    return m_size;
  }

  FORCEINLINE const Vector<uint8>&
  getPixels(){
    return m_pixels;
  }

  FORCEINLINE void
  fillFromPointer(uint8* data){
    memcpy(unconstPointer(m_pixels.data()),data,getNumberOfBytes());
  }

  FORCEINLINE void
  setFormat(FORMAT::E format){
    m_format = format;
  }

 private:
  
  /**
   * @brief the with of the image
  */
  Vector2I m_size;

  /**
   * @brief the size in bits of each pixel
  */
  int32 m_bitsPerPixel;

  /**
   * @brief the format of the data
  */
  FORMAT::E m_format;

  /**
   * @brief the pixels of the image
  */
  Vector<uint8> m_pixels;  

  
};

}


