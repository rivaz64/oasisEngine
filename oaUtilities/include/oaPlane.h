/**
 * @file oaPlane.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/12/2021
 */

#pragma once

#include "oaPrerequisitesUtilities.h"
#include "oaVector3f.h"

namespace oaEngineSDK {
/**
 * @brief classs for a plane in a 3D space
*/
class OA_UTILITY_EXPORT Plane
{
 public:
  /**
   * @brief default constructor for a plane
  */
  Plane() = default;

  /**
   * @brief gives directly the variables needed for a plane
   * @param _normal 
   * @param _d 
  */
  Plane(const Vector3f& normal, float d) :
    m_normal(normal.normalized()), m_d(d) {}

  /**
   * @brief a plane that passes throwth A, B, and C
   * @param A 
   * @param B 
   * @param C 
  */
  Plane(const Vector3f& A, const Vector3f& B, const Vector3f& C);

  Plane(const Vector3f& point, const Vector3f& m_normal);

  ~Plane() = default;

  /**
   * @brief getter for the normal
   * @return 
  */
  FORCEINLINE const Vector3f&
  getNormal() const {
    return m_normal;
  }
  
  /**
   * @brief getter for the member d
   * @return 
  */
  FORCEINLINE float 
  getD() const {
    return m_d;
  }

  /**
   * @brief calculates the transform matrix for reflecting an object in this plane
   * @return 
  */
  Matrix4f
  reflection();
 
 private:
  /**
    * @brief the normal of the plane
   */
  Vector3f m_normal;

  /**
   * @brief the result of the dot product betweeen the normal and any vector in the plane
  */
  float m_d;

  friend class PlatformMath;
};

}



