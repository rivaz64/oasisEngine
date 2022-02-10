#include "oaFrustrum.h"
#include "oaVector3f.h"
#include "oaMatrix3f.h"

namespace oaEngineSDK{

void 
Frustum::calculate(const Vector3f& location, 
                   const Matrix3f& axis, 
                   const float nearPlaneDistance, 
                   const float farPlaneDistance, 
                   const float viewAngle, 
                   const float ratio)
{
  m_nearPlane = Plane(location+axis*Vector3f(0,0,nearPlaneDistance),axis*Vector3f(0,0,1));
  m_farPlane = Plane(location+axis*Vector3f(0,0,farPlaneDistance),axis*Vector3f(0,0,-1));

  float nh = Math::tan(viewAngle/2.f)*nearPlaneDistance;
  float nw = nh*ratio;
  float fh = Math::tan(viewAngle/2.f)*farPlaneDistance;
  float fw = fh*ratio;

  Vector3f nnw = location+axis*Vector3f(-nw,nh,nearPlaneDistance);
  Vector3f nne = location+axis*Vector3f(nw,nh,nearPlaneDistance);
  Vector3f fne = location+axis*Vector3f(fw,fh,farPlaneDistance);

  m_topPlane = Plane(nnw,nne,fne);

  Vector3f nsw = location+axis*Vector3f(-nw,-nh,nearPlaneDistance);
  Vector3f nse = location+axis*Vector3f(nw,-nh,nearPlaneDistance);
  Vector3f fse = location+axis*Vector3f(fw,-fh,farPlaneDistance);
  Vector3f fsw = location+axis*Vector3f(-fw,-fh,farPlaneDistance);

  m_bottomPlane = Plane(nsw,fse,nse);

  m_leftPlane = Plane(nne,fse,fne);
}

}

