/**
* @file oaTriangle.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 3/18/2022
*/

#pragma once

#include "oaPrerequisitesUtilities.h"
#include "oaVector3f.h"
#include "oaVector4f.h"
namespace oaEngineSDK{


/**
 * @brief a structure for all the information at a certain point of a Mesh
*/
struct Vertex{
  
  /**
   * @brief the location in a tridimencional space of this vetrex
  */
  Vector4f location;

  /**
   * @brief the normal at this vertex
  */
  Vector4f normal;

  /**
   * @brief the tangent at this vertex
  */
  Vector4f tangent;

  /**
   * @brief the bitangent at this vertex
  */
  Vector4f bitangent;

  /**
   * @brief the part of the texture that is going to be drawn at a certain point
  */
  Vector2f textureCord;

};

/**
 * @brief a geometrical triangle to be divided
*/
class OA_UTILITY_EXPORT Triangle
{
 public:
  Triangle() = default;

  Triangle(const Vector3f& point1, const Vector3f& point2, const Vector3f& point3) :
    m_point1(point1), m_point2(point2), m_point3(point3) {}

  /**
   * @brief separates the triangle cutting it by the given plane
   * @param plane 
  */
  bool
  separate(const Plane& plane,
           Vector<Vector3f>& points, 
           Vector<uint32>& finalIndexPositiveSide,
           Vector<uint32>& finalIndexNegativeSide,
           bool& isTriFront);

  
 private:

  Vector3f m_point1;
  Vector3f m_point2;
  Vector3f m_point3;

};


}

