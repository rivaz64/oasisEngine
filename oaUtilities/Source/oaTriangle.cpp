#include "oaTriangle.h"
#include "oaLine.h"

namespace oaEngineSDK{

void
analizeLine(const Plane& plane, const Vector3f& point1, const Vector3f& point2, Vector<Vector3f>& points){
  
  Vector3f intersection;
  if(Math::distance(plane,point1)*Math::distance(plane,point2) < 0.0f){
    Math::intersect(plane,Line(point1,point2),intersection);
    points.push_back(intersection);
  }
  return false;
}

void 
Triangle::separate(const Plane& plane)
{
  Vector<Vector3f> points;
  analizeLine(plane,m_point1,m_point2,points);
  analizeLine(plane,m_point2,m_point3,points);
  analizeLine(plane,m_point3,m_point1,points);
}


}
