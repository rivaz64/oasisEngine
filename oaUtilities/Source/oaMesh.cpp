/**
 * @file oaMesh.cpp
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/12/2021
 */

#include "oaMesh.h"
#include "oaVector3f.h"

void oaEngineSDK::Mesh::generateNormals()
{
  normals.clear();
  normals.resize(vertices.size());
  for (uint32 i = 0; i < triangles.size(); i+=3) {
    Vector3f normal;
    normal = (vertices[triangles[i] + 1] - vertices[triangles[i]]).cross(vertices[triangles[i] + 2] - vertices[triangles[i]]);
    normal = normal.normal();
    normals[i] = normal;
    normals[i+1] = normal;
    normals[i+2] = normal;
  }
}
