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
  SIZE_T m_width;

  /**
   * @brief the with of the image
  */
  SIZE_T height;

  /**
   * @brief the pixels of the image
  */
  uint8* data;  
};

}


