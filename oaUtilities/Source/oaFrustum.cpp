#include "oaFrustum.h"
#include "oaVector3f.h"
#include "oaVector4f.h"
#include "oaMatrix3f.h"
#include "oaMatrix4f.h"
#include "oaSphere.h"
#include "oaAABB.h"

namespace oaEngineSDK{

bool
comparePlaneToAABB(const Plane& plane, const Vector<Vector3f>& box){
  bool isIn = false;
  for(auto& point : box){
    if(Math::distance(plane, point) > 0){
      isIn = true;
      break;
    }
  }
  return isIn;
}

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

  Vector<Vector3f> points;

  points.resize(8);

  //nearNorthWest
  points[0] = location+axis*Vector3f(-nearWidth,nearHeight,nearPlaneDistance);
  //nearNorthEast
  points[1] = location+axis*Vector3f(nearWidth,nearHeight,nearPlaneDistance);
  //nearSouthWest
  points[2] = location+axis*Vector3f(-nearWidth,-nearHeight,nearPlaneDistance);
  //nearSouthEast
  points[3] = location+axis*Vector3f(nearWidth,-nearHeight,nearPlaneDistance);
  //farNorthWest
  points[4] = location+axis*Vector3f(-farWidth,farHeight,farPlaneDistance);
  //farNorthEast
  points[5] = location+axis*Vector3f(farWidth,farHeight,farPlaneDistance);
  //farSouthWest
  points[6] = location+axis*Vector3f(-farWidth,-farHeight,farPlaneDistance);
  //farSouthEast
  points[7] = location+axis*Vector3f(farWidth,-farHeight,farPlaneDistance);
  
  return points;
}

bool 
Frustum::isInside(const Vector3f& point) const
{
  return 
    Math::distance(m_nearPlane, point) > 0 &&
    Math::distance(m_farPlane, point) > 0 &&
    Math::distance(m_topPlane, point) > 0 &&
    Math::distance(m_bottomPlane, point) > 0 &&
    Math::distance(m_rightPlane, point) > 0 && 
    Math::distance(m_leftPlane, point) > 0;
}

bool 
Frustum::isInside(const Sphere& sphere, const Matrix4f& transform) const
{ 
  auto center = (transform * Vector4f(sphere.getCenter(),1.0)).xyz;
  auto scale = (transform * Vector4f(1,1,1,1)).xyz-(transform * Vector4f(0,0,0,1)).xyz; 
  auto radius = sphere.getRadius()*Math::max(Math::max(scale.x,scale.y),scale.z);
  
  return 
    Math::distance(m_nearPlane, center) > -sphere.getRadius() &&
    Math::distance(m_farPlane, center) > -sphere.getRadius() &&
    Math::distance(m_topPlane, center) > -sphere.getRadius() &&
    Math::distance(m_bottomPlane, center) > -sphere.getRadius() &&
    Math::distance(m_rightPlane, center) > -sphere.getRadius() &&
    Math::distance(m_leftPlane, center) > -sphere.getRadius();
}

bool 
Frustum::isInside(const AABB& box, const Matrix4f& transform) const
{
  auto points = box.getPoints();
  for(auto& point : points){
    point = (transform*Vector4f(point,1.0f)).xyz;
  }
  return
   comparePlaneToAABB(m_nearPlane,points) &&
   comparePlaneToAABB(m_farPlane,points) &&
   comparePlaneToAABB(m_topPlane,points) &&
   comparePlaneToAABB(m_bottomPlane,points) &&
   comparePlaneToAABB(m_rightPlane,points) &&
   comparePlaneToAABB(m_leftPlane,points);

}

}

