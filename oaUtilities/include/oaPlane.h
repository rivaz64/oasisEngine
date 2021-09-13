/**
 * @file oaPlane.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/12/2021
 */

#pragma once
#include"oaPrerequisitesUtilities.h"

namespace oaEngineSDK {
/**
 * @brief classs for a plane in a 3D space
*/
class OA_UTILITY_EXPORT Plane
{
  /**
   * @brief the normal of the plane
  */
  Vector3f normal;

  /**
   * @brief the result of the dot product betweeen the normal and any vector in the plane
  */
  float d;
public:

  Plane() = default;
  /**
   * @brief gives directly the variables needed for a plane
   * @param _normal 
   * @param _d 
  */

  Plane(const Vector3f& _normal, float _d) :normal(_normal), d(_d) {}
  /**
   * @brief a plane that passes throwth A, B, and C
   * @param A 
   * @param B 
   * @param C 
  */
  Plane(Vector3f& A, Vector3f& B, Vector3f& C);

  FORCEINLINE Vector3f 
    getNormal() {
    return normal;
  }
  
  FORCEINLINE float 
    getD() {
    return d;
  }

  /**
   * @brief distance between the point p and thit plane
   * @param p 
   * @return 
  */
  float 
    distance(Vector3f& p);

  /**
   * @brief calculates the transform matrix for reflecting an object in this plane
   * @return 
  */
  Matrix4f
    reflection();
};

}



