/**
* @file oaModel.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#include "oaModel.h"
#include "oaStaticMesh.h"

namespace oaEngineSDK{

Model::Model(SIZE_T numOfMeshes)
{
  m_meshes.resize(numOfMeshes);
}

Vector3f 
Model::getCenter()
{
  Vector3f center(0,0,0);
  float totalVertices = 0;
  for(auto& mesh : m_meshes){
    auto vertices = cast<StaticMesh>(mesh)->getVertex();
    totalVertices += vertices.size();
    for(auto& vertex : vertices){
      center += vertex.location.xyz;
    }
  }
  return center/totalVertices;
}

float 
Model::farestPoint(const Vector3f& point)
{
  float maxDistance = 0;
  for(auto& mesh : m_meshes){
    auto vertices = cast<StaticMesh>(mesh)->getVertex();
    for(auto& vertex : vertices){
      auto distance = (point-vertex.location.xyz).magnitud();
      if(maxDistance<distance){
        maxDistance = distance;
      }
    }
  }
  return maxDistance;
}

}

