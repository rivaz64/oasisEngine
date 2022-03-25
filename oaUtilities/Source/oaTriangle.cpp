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
           //Vector<uint32>& finalIndexPositiveSide,
           Vector<uint32>& finalIndexNegativeSide)
{
  Vector<int32> index;
 
  int32 otherside;
  
  float dist1 = Math::distance(plane,m_point1);
  float dist2 = Math::distance(plane,m_point2);
  float dist3 = Math::distance(plane,m_point3);

  if(analizeLine(plane,m_point1,m_point2,points)){    
    index.push_back(1);
    if(analizeLine(plane,m_point2,m_point3,points)){
      index.push_back(4);
      index.push_back(2);
      otherside = 1;
    }
    else if(analizeLine(plane,m_point3,m_point1,points)){
      index.push_back(2);
      index.push_back(4);
      otherside = 0;
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
    otherside = 2;
  }
  else{
    return false;
  }

  for(int32 i=0;i<3;i++){
    if(i==otherside){
    
    }
    else{
      finalIndexNegativeSide.push_back(3);
      finalIndexNegativeSide.push_back(index[i]);
      finalIndexNegativeSide.push_back(index[i+1]);
    }
    
  }
  return true;
}


}
