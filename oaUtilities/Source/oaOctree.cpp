#include "oaOctree.h"

namespace oaEngineSDK{

Vector<Plane>
Octree::getPlanes(const Vector3f& center)
{
  return {
    Plane(center,center+Vector3f(0,0,1),center+Vector3f(0,1,0)),
    Plane(center,center+Vector3f(0,1,0),center+Vector3f(1,0,0)),
    Plane(center,center+Vector3f(1,0,0),center+Vector3f(0,0,1))
  };

}

}

