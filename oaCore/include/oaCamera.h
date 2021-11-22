/**
* @file oaCamera.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/9/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaVector3f.h"
#include "oaMatrix3f.h"
#include "oaMatrix4f.h"
#include "oaVector2f.h"
#include "oaBuffer.h"
#include "oaObject.h"

namespace oaEngineSDK{

class OA_CORE_EXPORT Camera
{
 public:

  Camera();

  /**
   * @brief if the proyection atributes have changed aplies the nesesary calculations
  */
  void
  updateProyection();

  /**
   * @brief if the view atributes have changed aplies the nesesary calculations
  */
  void
  updateView();

  /**
   * @brief the transform matrix so that is seems like a camera
   * @return 
  */
  void
  setCamera();

  /**
   * @brief moves the camera 
   * @param delta
  */
  void
  moveCamera(const Vector3f& delta);

  /**
   * @brief sets 
   * @param newLocation 
  */
  void
  lookAt(const Vector3f& newLocation);

  /**
   * @brief rotates the camera 
   * @param delta the delta of the mouse position
  */
  void
  rotateWithMouse(const Vector2f& delta);

  /**
   * @brief if the object is observerd by the camera
   * @param _location 
   * @return 
  */
  bool
  isInFrustrum(const Vector4f& _location);

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
   * @brief where the camera is
  */
  Vector3f location;

  /**
   * @brief the direction the camera is looking
  */
  Vector3f lookingAt;

  /**
   * @brief where it is the up of the camera
  */
  Vector3f up;

  /**
   * @brief the local axis of the camera
  */
  Matrix3f axis;

  /**
   * @brief the view matrix of this camera
  */
  Matrix4f viewMatrix;

  /**
   * @brief the buffer of the viewMatrix
  */
  SPtr<Buffer> view;

  /**
   * @brief the buffer of the proyectionMatrix
  */
  SPtr<Buffer> proyection;
};

}


