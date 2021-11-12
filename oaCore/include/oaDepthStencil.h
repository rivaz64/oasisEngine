/**
* @file oaDepthStencil.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/11/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaFlags.h"
namespace oaEngineSDK{

struct DepthStencilDesc{
  uint32 MipSlice;
  DS_DIMENSION viewDimension;
  FORMAT format;
};


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
  init(DepthStencilDesc /*descritor*/, SPtr<Texture> /*texture*/) {return true;}

};

}


