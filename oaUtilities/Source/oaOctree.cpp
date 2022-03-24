#include "oaOctree.h"

namespace oaEngineSDK{

Vector<Plane>
Octree::getPlanes()
{
  
  //auto& pos = m_root->location;
  auto pos = Vector3f(.125,.25,.375);
  return {
    Plane( pos,pos+Vector3f(0,0,1),pos+Vector3f(0,1,0)),
    Plane( pos,pos+Vector3f(0,1,0),pos+Vector3f(1,0,0)),
    Plane( pos,pos+Vector3f(1,0,0),pos+Vector3f(0,0,1))
  };

}

}

