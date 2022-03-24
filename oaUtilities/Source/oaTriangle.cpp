#include "oaTriangle.h"
#include "oaLine.h"

namespace oaEngineSDK{

bool
analizeLine(const Plane& plane, const Vector3f& point1, const Vector3f& point2, Vector<Vector3f>& points){
  
  Vector3f intersection;
  if(Math::distance(plane,point1)*Math::distance(plane,point2) < 0.0f){
    Math::intersect(plane,Line(point1,point2),intersection);
    points.push_back(intersection);
    return  true;
  }
  return false;
}

bool 
Triangle::separate(const Plane& plane,
           Vector<Vector3f>& points, 
           Vector<uint32>& finalIndexPositiveSide,
           Vector<uint32>& finalIndexNegativeSide)
{
  Vector<int32> index;
 
  int32 actualIndex = 3;
  int32 init = 1;

  if(analizeLine(plane,m_point1,m_point2,points)){
    index.push_back(1);
    if(analizeLine(plane,m_point2,m_point3,points)){
      index.push_back(4);
      index.push_back(2);
    }
    else if(analizeLine(plane,m_point3,m_point1,points)){
      index.push_back(2);
      index.push_back(4);
    }
    else{
      return false;
    }
    index.push_back(0);
  }
  else if(analizeLine(plane,m_point2,m_point3,points) && analizeLine(plane,m_point3,m_point1,points)){
    index.push_back(2);
    index.push_back(4);
    index.push_back(0);
    index.push_back(1);
  }
  else{
    return false;
  }

  for(int32 i=0;i<3;i++){
    finalIndex.push_back(3);
    finalIndex.push_back(index[i]);
    finalIndex.push_back(index[i+1]);
  }
  return true;
}


}
