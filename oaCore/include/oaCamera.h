/**
* @file oaCamera.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/9/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"
#include "oaVector4f.h"
#include "oaMatrix3f.h"
#include "oaMatrix4f.h"
#include "oaVector2f.h"
#include "oaPlane.h"
#include "oaFrustum.h"

namespace oaEngineSDK{

/**
 * @brief a virtual camera
*/
class OA_CORE_EXPORT Camera
{
 public:

  Camera();

  /**
   * @brief initializes the camera
   * @param ratio height / width
   * @param viewAngle in radians
   * @param nearPlaneDistance 
   * @param farPlaneDistance 
  */
  void
  init(const float ratio,
       const float viewAngle = Math::PI/4.f,
       const float nearPlaneDistance = 1.0f,
       const float farPlaneDistance = 600.0f);

  /**
   * @brief updates the campera
  */
  void 
  update();

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
   * @brief sets the global location of the camera
  */
  void
  setLocation(const Vector3f& newLocation);

  /**
   * @brief sets the rotation of the camera
   * @param newRotation 
  */
  //void
  //setRotation(const Vector3f& newRotation);

  /**
   * @brief getter for the view matrix
   * @return the viewMatrix
  */
  FORCEINLINE const Matrix4f&
  getViewMatrix(){
    return m_viewMatrix;
  }

  /**
   * @brief getter for the view getProyectionMatrix
   * @return the viewMatrix
  */
  FORCEINLINE const Matrix4f&
  getProjectionMatrix(){
    return m_projectionMatrix;
  }

  /**
   * @brief getter for the view matrix
   * @return the viewMatrix
  */
  FORCEINLINE const Vector3f&
  getLocation(){
    return m_location;
  }

  FORCEINLINE const Matrix3f&
  getAxisMatrix(){
    return m_axis;
  }

  FORCEINLINE float
  getNearPlaneDistance(){
    return m_nearPlaneDistance;
  }

  FORCEINLINE float
  getFarPlaneDistance(){
    return m_farPlaneDistance;
  }

  FORCEINLINE float
  getViewAngle(){
    return m_viewAngle;
  }

  FORCEINLINE float
  getRatio(){
    return m_ratio;
  }


 public:
  /**
   * @brief how far the camera can see
  */
  float m_farPlaneDistance;

  /**
   * @brief the nearest that the camera can see
  */
  float m_nearPlaneDistance;

  /**
   * @brief the angle of the openes of the camera
  */
  float m_viewAngle;

  /**
   * @brief the ratio between the with and the height of the camera
  */
  float m_ratio;

  /**
   * @brief where the camera is
  */
  Vector3f m_location;

  /**
   * @brief the direction the camera is looking
  */
  Vector3f m_lookingAt;

  /**
   * @brief where it is the up of the camera
  */
  Vector3f m_up;

  union{

    /**
     * @brief the local axis of the camera
    */
    Matrix3f m_axis;

    struct{
    
      Vector3f m_axisX;

      Vector3f m_axisY;

      Vector3f m_axisZ;
    
    };

  };
  

  /**
   * @brief the view matrix of this camera
  */
  Matrix4f m_viewMatrix;

  /**
   * @brief the projection matrix of this camera
  */
  Matrix4f m_projectionMatrix;

  /**
   * @brief dirty flags for the view matrix
  */
  uint8 dirtyFlags;
};

}


