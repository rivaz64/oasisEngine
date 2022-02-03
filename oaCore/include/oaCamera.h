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
#include "oaPlane.h"

namespace oaEngineSDK{

/**
 * @brief a virtual camera
*/
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
   * @brief if the Actor is observerd by the camera
   * @param _location 
   * @return 
  */
  bool
  isInFrustrum(const Vector3f& _location);

  /**
   * @brief creates the frustrum
  */
  void
  createFrustrum();

  
  /**
   * @brief sees the Actors in a scene
   * @param the sceen to be sceen
   * @param the Actors seen by this camera
  */
  void
  seeActors(SPtr<Actor> scene,Vector<SPtr<Actor>>& seenActors);

 public:
  /**
   * @brief how far the camera can see
  */
  float m_farPlane;

  /**
   * @brief the nearest that the camera can see
  */
  float m_nearPlane;

  /**
   * @brief the angle of the openes of the camera
  */
  float m_angle;

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
  Matrix4f viewMatrix;

  /**
   * @brief the buffer of the viewMatrix
  */
  SPtr<Buffer> view;

  /**
   * @brief the near plane of the frustrum
  */
  Plane nearP;

  /**
   * @brief the far plane of the frustrum
  */
  Plane farP;

  /**
   * @brief the top plane of the frustrum
  */
  Plane topP;

  /**
   * @brief the bottom plane of the frustrum
  */
  Plane bottomP;

  /**
   * @brief the near left of the frustrum
  */
  Plane leftP;

  /**
   * @brief the right plane of the frustrum
  */
  Plane rightP;

  /**
   * @brief the buffer of the proyectionMatrix
  */
  SPtr<Buffer> proyection;

  /**
   * @brief dirty flags for the view matrix
  */
  uint8
  dirtyFlags;
};

}


