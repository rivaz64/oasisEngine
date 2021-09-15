/**
 * @file oaMesh.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/12/2021
 */

#pragma once
#include"oaPrerequisitesUtilities.h"

namespace oaEngineSDK {
class OA_UTILITY_EXPORT Mesh
{
 public:
  FORCEINLINE void setVertices(const Vector<Vector3f>& _vertices) {
    vertices = _vertices;
  }
  FORCEINLINE void setTriangles(const Vector<uint32>& _triangles) {
    triangles = _triangles;
    faces = triangles.size() / 3;
  }
  /**
   * @brief generate normals automaticly
  */
  void generateNormals();

 private:
   /**
   * @brief the number of tris of the mesh
  */
   uint32 faces;
   /**
    * @brief all the vertices of the mesh
   */
   Vector<Vector3f> vertices;
   /**
    * @brief the vertices that each triangle uses
   */
   Vector<uint32> triangles;
   /**
    * @brief all the normals of the mesh
   */
   Vector<Vector3f> normals;
};
}


