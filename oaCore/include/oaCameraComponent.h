/**
* @file oaCameraComponent.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/2/2021
*/

#pragma once

#include "oaComponent.h"

namespace oaEngineSDK{

class OA_CORE_EXPORT CameraComponent :
  public Component
{
 public:
  
  COMPONENT_TYPE::E
  getType() override;

  /**
   * @brief getter for the camera
   * @return 
  */
  FORCEINLINE WPtr<Camera>
  getCamera(){
    return m_camera;
  }

  /**
   * @brief sets the camera
   * @param camera 
  */
  FORCEINLINE void
  setCamera(WPtr<Camera> camera){
    m_camera = camera;
  }

  void
  update(WPtr<Actor> actor) override;

  /**
   * @brief if true draws the 
  */
  bool 
  m_debug = false;

 private:

  /**
   * @brief the camera that this component has
  */
  WPtr<Camera> m_camera;
};

}


