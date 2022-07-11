/**
* @file oaModel.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#include "oaModel.h"
#include "oaMesh.h"
#include "oaMaterial.h"
#include "oaResoureManager.h"

namespace oaEngineSDK{

Model::Model(SIZE_T numOfMeshes)
{
  m_meshes.resize(numOfMeshes);
}

void 
Model::save(Serializer& serializer)
{ 
  auto num = m_meshes.size();
  serializer.encodeNumber(m_meshes.size());
  for(SIZE_T n=0; n<num; ++n){
    m_meshes[n]->save(serializer);
    if(!m_materials[n].expired()){
      auto material = m_materials[n].lock();
      serializer.encodeString(material->getName());
    }
  }
}

void 
Model::load(Serializer& serializer)
{
  auto num = serializer.decodeNumber();
  m_meshes.resize(num);
  m_materials.resize(num);
  for(SIZE_T n=0; n<num; ++n){
    m_meshes[n] = makeSPtr<Mesh<Vertex>>();
    m_meshes[n]->load(serializer);
    auto materialName = serializer.decodeString();
    addMaterial(ResoureManager::instance().m_materials[materialName]);
  }
}

Vector3f 
Model::getCenter()
{
  Vector3f center(0,0,0);
  float totalVertices = 0;
  for(auto& mesh : m_meshes){
    auto vertices = mesh->getVertex();
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
    auto vertices = mesh->getVertex();
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

