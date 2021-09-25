/**
 * @file oaPlane.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/12/2021
 */

#pragma once
#include "oaPrerequisitesUtilities.h"

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

  Plane(const Vector3f& _normal, float _d) :normal(_normal), d(_d) {}
  /**
   * @brief a plane that passes throwth A, B, and C
   * @param A 
   * @param B 
   * @param C 
  */
  Plane(const Vector3f& A, const Vector3f& B, const Vector3f& C);

  ~Plane() = default;

  /**
   * @brief getter for the normal
   * @return 
  */
  FORCEINLINE Vector3f 
  getNormal() {
    return normal;
  }
  
  /**
   * @brief getter for the member d
   * @return 
  */
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

  /**
   * @brief calculates the point where a line intersects a plane
   * @param l 
   * @param point where the line intersects
   * @return if it intersects or not
  */
  bool
  intersect(Line& l,Vector3f& point);

  /**
   * @brief calculates the point where 3 planes intersect
   * @param p1 
   * @param p2 
   * @param point 
   * @return if it intersects or not
  */
  bool
  intersect(Plane& p1, Plane& p2, Vector3f& point);

  /**
   * @brief calculates the line where 2 planes intersect
   * @param p 
   * @param intersection 
   * @return 
  */
  bool
  intersect(Plane& p, Line& intersection);
 
  /**
    * @brief the normal of the plane
   */
  Vector3f normal;

  /**
   * @brief the result of the dot product betweeen the normal and any vector in the plane
  */
  float d;
};

}



