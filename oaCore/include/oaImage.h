/**
* @file oaImage.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/12/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"

namespace oaEngineSDK{

class Image
{
 public:
  
  /**
   * @brief the with of the image
  */
  uint32 m_width;

  /**
   * @brief the with of the image
  */
  uint32 m_height;

  /**
   * @brief the pitch of this image
  */
  uint32 m_pitch;

  /**
   * @brief the pixels of the image
  */
  uint8* m_pixels;  
};

}


