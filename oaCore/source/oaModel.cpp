/**
* @file oaModel.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#include "oaModel.h"
#include "oaStaticMesh.h"
#include "oaMaterial.h"
#include "oaResoureManager.h"

namespace oaEngineSDK{

void 
Model::save(Serializer& serializer)
{ 
  serializer.encodeNumber(getType());
  serializer.encodeString(getName());

  if(!m_mesh.expired()){
    serializer.encodeNumber(1);
    auto mesh = m_mesh.lock();
    serializer.encodeString(mesh->getName());
  }
  else{
    serializer.encodeNumber(0);
  }

  if(!m_material.expired()){
    serializer.encodeNumber(1);
    auto material = m_material.lock();
    serializer.encodeString(material->getName());
  }
  else{
    serializer.encodeNumber(0);
  }
  
}

void 
Model::load(Serializer& serializer)
{
  setName(serializer.decodeString());
  auto b = serializer.decodeNumber();
  auto& resourses = ResoureManager::instance();
  if(b == 1){
    auto meshName = serializer.decodeString();
    m_mesh = cast<StaticMesh>(resourses.getResourse(meshName));
  }

  b = serializer.decodeNumber();

  if(b == 1){
    auto materialhName = serializer.decodeString();
    m_material = cast<Material>(resourses.getResourse(materialhName));
  }
  else{
    m_material = resourses.m_defaultMaterial;
  }
  
}

Vector3f 
Model::getCenter()
{
  Vector3f center(0,0,0);
  //float totalVertices = 0;
  //for(auto& mesh : m_meshes){
  //  auto vertices = mesh->getVertex();
  //  totalVertices += vertices.size();
  //  for(auto& vertex : vertices){
  //    center += vertex.location.xyz;
  //  }
  //}
  return center;//totalVertices;
}

float 
Model::farestPoint(const Vector3f& point)
{
  float maxDistance = 0;
  //for(auto& mesh : m_meshes){
  //  auto vertices = mesh->getVertex();
  //  for(auto& vertex : vertices){
  //    auto distance = (point-vertex.location.xyz).magnitud();
  //    if(maxDistance<distance){
  //      maxDistance = distance;
  //    }
  //  }
  //}
  return maxDistance;
}

}

