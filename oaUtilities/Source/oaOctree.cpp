#include "oaOctree.h"

namespace oaEngineSDK{

Vector<Plane>
Octree::getPlanes()
{
  return {
    Plane(m_center,m_center+Vector3f(0,0,1),m_center+Vector3f(0,1,0)),//1,0,0
    Plane(m_center,m_center+Vector3f(1,0,0),m_center+Vector3f(0,0,1)),//0,1,0
    Plane(m_center,m_center+Vector3f(0,1,0),m_center+Vector3f(1,0,0)) //0,0,1
    
  };

}

Vector<Vector3f>
Octree::getCenters(float size)
{
  Vector3f newPos;
  Vector<Vector3f> centers;
  for(newPos.z = -1; newPos.z < 2; newPos.z += 2){
    for(newPos.y = -1; newPos.y < 2; newPos.y += 2){
      for(newPos.x = -1; newPos.x < 2; newPos.x += 2){
        centers.push_back(newPos*size/2.f+m_center);
      }
    }
  }
  return centers;
}

}

