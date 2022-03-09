/**
 * @file oaPlane.cpp
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/12/2021
 */

#include "oaVector3f.h"
#include "oaVector4f.h"
#include "oaMatrix4f.h"
#include "oaLine.h"
#include "oaPlane.h"

namespace oaEngineSDK {

Plane::Plane(const Vector3f& A, const Vector3f& B, const Vector3f& C)
{
  m_normal = Vector3f::cross(B - A,C - A).normalized();
  m_d = -Vector3f::dot(m_normal,A);
}

Plane::Plane(const Vector3f & point, const Vector3f & _normal)
{
  m_normal = _normal;
  m_d = -Vector3f::dot(m_normal,point);
}

Matrix4f
Plane::reflection()
{
  float xy = -2.f * m_normal.x * m_normal.y;
  float xz = -2.f * m_normal.x * m_normal.z;
  float yz = -2.f * m_normal.y * m_normal.z;
  return Matrix4f(
    Vector4f(1.f-2.f*m_normal.x*m_normal.x,xy,xz,-2.f*m_normal.x*m_d),
    Vector4f(xy,1.f - 2.f * m_normal.y * m_normal.y, yz,-2.f * m_normal.y*m_d),
    Vector4f(xz,yz,1.f - 2.f * m_normal.z * m_normal.z,-2.f * m_normal.z*m_d),
    Vector4f(0.f,0.f,0.f,1.f)
    );
}

}

