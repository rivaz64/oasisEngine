/**
* @file oaCameraComponent.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/11/2021
*/

#pragma once

#include "oaComponent.h"

namespace oaEngineSDK{

class oaCameraComponent :
  public Component
{
 public:
  
  /**
   * @brief getter for the camera
   * @return 
  */
  FORCEINLINE SPtr<Camera> 
  getCamera(){
    return m_camera;
  }

  /**
   * @brief sets the camera
   * @param camera 
  */
  FORCEINLINE void
  setCamera(SPtr<Camera> camera){
    m_camera = camera;
  }

 private:

  /**
   * @brief the camera that this component has
  */
  SPtr<Camera> m_camera;
};

}


