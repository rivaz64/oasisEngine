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
  
  /**
   * @brief getter for the camera
   * @return 
  */
  FORCEINLINE SPtr<Camera>&
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

  void
  update(SPtr<Actor> actor) override;

  /**
   * @brief if true draws the 
  */
  bool 
  m_debug = false;

 private:

  /**
   * @brief the camera that this component has
  */
  SPtr<Camera> m_camera;
};

}


