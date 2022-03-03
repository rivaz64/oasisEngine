#include "oaFrustum.h"
#include "oaVector3f.h"
#include "oaMatrix3f.h"

namespace oaEngineSDK{

Frustum::Frustum(const Vector3f& location, 
                 const Matrix3f& axis, 
                 const float nearPlaneDistance, 
                 const float farPlaneDistance, 
                 const float viewAngle, 
                 const float ratio)
{
  calculatePlanes(location,axis,nearPlaneDistance,farPlaneDistance,viewAngle,ratio);
}
void 
Frustum::calculatePlanes(const Vector3f& location, 
                         const Matrix3f& axis, 
                         const float nearPlaneDistance, 
                         const float farPlaneDistance, 
                         const float viewAngle, 
                         const float ratio)
{

  auto points = calculatePoints(location,axis,nearPlaneDistance,farPlaneDistance,viewAngle,ratio);

  m_nearPlane = Plane(points[1],points[0],points[2]);
  m_farPlane = Plane(points[4],points[5],points[6]);
  m_topPlane = Plane(points[0],points[1],points[4]);
  m_bottomPlane = Plane(points[3],points[2],points[6]);
  m_leftPlane = Plane(points[2],points[0],points[4]);
  m_rightPlane = Plane(points[1],points[3],points[5]);
}

Vector<Vector3f> 
Frustum::calculatePoints(const Vector3f& location, 
                         const Matrix3f& axis, 
                         const float nearPlaneDistance, 
                         const float farPlaneDistance, 
                         const float viewAngle, 
                         const float ratio)
{

  float nearHeight = Math::tan(viewAngle/2.f)*nearPlaneDistance;
  float nearWidth = nearHeight*ratio;
  float farHeight = Math::tan(viewAngle/2.f)*farPlaneDistance;
  float farWidth = farHeight*ratio;

  Vector3f nearNorthWest = location+axis*Vector3f(-nearWidth,nearHeight,nearPlaneDistance);
  Vector3f nearNorthEast = location+axis*Vector3f(nearWidth,nearHeight,nearPlaneDistance);
  Vector3f nearSouthWest = location+axis*Vector3f(-nearWidth,-nearHeight,nearPlaneDistance);
  Vector3f nearSouthEast = location+axis*Vector3f(nearWidth,-nearHeight,nearPlaneDistance);

  Vector3f farNorthWest = location+axis*Vector3f(-farWidth,farHeight,farPlaneDistance);
  Vector3f farNorthEast = location+axis*Vector3f(farWidth,farHeight,farPlaneDistance);
  Vector3f farSouthWest = location+axis*Vector3f(-farWidth,-farHeight,farPlaneDistance);
  Vector3f farSouthEast = location+axis*Vector3f(farWidth,-farHeight,farPlaneDistance);

  return {nearNorthWest, 
          nearNorthEast, 
          nearSouthWest, 
          nearSouthEast, 
          farNorthWest, 
          farNorthEast, 
          farSouthWest, 
          farSouthEast};
}

bool 
Frustum::isInside(const Vector3f& point) const
{
  return 
    Math::distance(m_nearPlane,point)>0 &&
    Math::distance(m_farPlane,point)>0 &&
    Math::distance(m_topPlane,point)>0 &&
    Math::distance(m_bottomPlane,point)>0 &&
    Math::distance(m_rightPlane,point)>0 && 
    Math::distance(m_leftPlane,point)>0;
}

}

