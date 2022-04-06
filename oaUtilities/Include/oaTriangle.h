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
  Vertex() = default;

  Vertex(const Vector4f& _location,const Vector4f& _normal,const Vector2f& _textureCord) :
    location(_location), normal(_normal),textureCord(_textureCord){}
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

  Triangle(const Vertex& point1, const Vertex& point2, const Vertex& point3) :
    m_point1(point1), m_point2(point2), m_point3(point3) {}

  /**
   * @brief separates the triangle cutting it by the given plane
   * @param plane 
  */
  bool
  separate(const Plane& plane,
           Vector<Vertex>& points, 
           Vector<uint32>& finalIndexPositiveSide,
           Vector<uint32>& finalIndexNegativeSide,
           bool& isTriFront);

  
 private:

  Vertex m_point1;
  Vertex m_point2;
  Vertex m_point3;

};


}

