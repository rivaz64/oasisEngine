/**
* @file oaCamera.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/9/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaMatrix4f.h"
#include "oaBuffer.h"

namespace oaEngineSDK{

class OA_CORE_EXPORT Camera
{
 public:

   Camera();

  /**
   * @brief the transform matrix so that is seems like a camera
   * @return 
  */
  void
  setCamera();

 public:
  /**
   * @brief how far the camera can see
  */
  float farPlane;

  /**
   * @brief the nearest that the camera can see
  */
  float nearPlane;

  /**
   * @brief the angle of the openes of the camera
  */
  float angle;

  /**
   * @brief the ratio between the with and the height of the camera
  */
  float ratio;

  /**
   * @brief the buffer of the viewMatrix
  */
  SPtr<Buffer> buffer;
};

}


