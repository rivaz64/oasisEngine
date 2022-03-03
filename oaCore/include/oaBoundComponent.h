/**
* @file oaBoundComponent.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/9/2021
*/

#pragma once

#include "oaComponent.h"
#include "oaSphere.h"

namespace oaEngineSDK{

class BoundComponent :
    public Component
{
 public:

  /**
   * @brief calculates the boundings for this mesh
  */
  void
  calculateBounding(){}

 private:
  
  //SPtr<

  /**
   * @brief the bounding shere of this mesh
  */
  Sphere m_boundingSphere;
};

}


