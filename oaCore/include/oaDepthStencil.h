/**
* @file oaDepthStencil.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/11/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaFlags.h"

namespace oaEngineSDK{

/**
 * @brief the desctriptor for the depth stencil
*/
struct DepthStencilDesc{
  
  /**
   * @brief th number of mip Silce
  */
  uint32 MipSlice;

  /**
   * @brief the dimecions of the view
  */
  DS_DIMENSION::E viewDimension;

  /**
   * @brief the format of the depth stencil
  */
  FORMAT::E format;
};

/**
 * @brief a wraper for the depth stencil
*/
class DepthStencil
{
 public:

  virtual ~DepthStencil() {}

  /**
   * @brief initializes a depthstencil
   * @param desctritor 
   * @param texture
   * @return 
  */
  virtual bool
  init(SPtr<Texture> /*texture*/) {return true;}

  /**
   * @brief releases the depth stencil
  */
  virtual void
  release(){}
};

}


