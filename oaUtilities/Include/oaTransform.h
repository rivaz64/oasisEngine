/**
 * @file oaTransform.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */

#pragma once

#include "oaPrerequisitesUtilities.h"
#include "oaVector3f.h"
#include "oaMatrix4f.h"

namespace oaEngineSDK{

class OA_UTILITY_EXPORT Transform
{
 public:
  
  Transform(const Vector3f& location = Vector3f(0,0,0),
            const Vector3f& scale = Vector3f(1,1,1),
            const Vector3f& rotation = Vector3f(0,0,0)) :
            m_location(location),
            m_scale(scale),
            m_rotation(rotation){}


  /**
   * @brief sets the location of this transfomr
   * @param location 
  */
  FORCEINLINE void
  setLocation(const Vector3f& location){
    m_location = location;
  }

  /**
   * @brief sets the scale of this transfomr
   * @param scale 
  */
  FORCEINLINE void
  setScale(const Vector3f& scale){
    m_scale = scale;
  }

  /**
   * @brief sets the rotation of this transfomr
   * @param rotation 
  */
  FORCEINLINE void
  setRotation(const Vector3f& rotation){
    m_rotation = rotation;
  }

  /**
   * @brief gets the location of this transform
   * @return 
  */
  FORCEINLINE const Vector3f&
  getLocation(){
    return m_location;
  }

  /**
   * @brief gets the scale of this transform
   * @return 
  */
  FORCEINLINE const Vector3f&
  getScale(){
    dirty = true;
    return m_scale;
  }

  /**
   * @brief gets the rotation of this transform
   * @return 
  */
  FORCEINLINE const Vector3f&
  getRotation(){
    dirty = true;
    return m_rotation;
  }

  /**
   * @brief gets the matrix of this transform
   * @return 
  */
  FORCEINLINE const Matrix4f&
  getMatrix(){
    if(dirty){
      dirty = false;
      calculate();
    }
    return m_matrix;
  }



 private:

  /**
   * @brief calculates the matrix fo this transform
  */
  void 
  calculate();

 private:
  /**
   * @brief where the Actor is in a 3D space
  */
  Vector3f m_location;

  /**
   * @brief the scale compared with the original imported model
  */
  Vector3f m_scale;

  /**
   * @brief how the Actor is rotated
  */
  Vector3f m_rotation;

  /**
   * @brief the transform of this Actor with origin at his parent
  */
  Matrix4f m_matrix;

  /**
   * @brief dirty flag for the getter of the transform
  */
  bool dirty = true;
};

}


