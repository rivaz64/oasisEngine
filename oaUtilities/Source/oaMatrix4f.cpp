#include"oaVector4f.h"
#include"oaVector3f.h"
#include"oaMatrix3f.h"
#include "oaMatrix4f.h"

namespace oaEngineSDK {
Matrix4f::Matrix4f(float f)
{
  a = { f,0.f,0.f,0.f };
  b = { 0.f,f,0.f,0.f };
  c = { 0.f,0.f,f,0.f };
  d = { 0.f,0.f,0.f,f };
}

Vector4f& 
Matrix4f::operator[](uint8 i)
{
  return ((&a)[i]);
}

Matrix4f 
oaEngineSDK::Matrix4f::operator+(Matrix4f& m)
{
  return { m.a + a,m.b + b,m.c + c,m.d + d };
}

void 
oaEngineSDK::Matrix4f::operator+=(Matrix4f& m)
{
  a += m.a;
  b += m.b;
  c += m.c;
  d += m.d;
}
Matrix4f 
Matrix4f::operator-(Matrix4f& m)
{
  return { a - m.a,b - m.b,c - m.c,d - m.d };
}
void 
Matrix4f::operator-=(Matrix4f& m)
{
  a -= m.a;
  b -= m.b;
  c -= m.c;
  d -= m.d;
}
Matrix4f 
Matrix4f::operator*(float m)
{
  return { a * m,b * m,c * m,d * m };
}
void
Matrix4f::operator*=(float m)
{
  a *= m;
  b *= m;
  c *= m;
  d *= m;
}
Vector4f 
Matrix4f::operator*(Vector4f& v)
{
  return { a.dot(v),b.dot(v),c.dot(v),d.dot(v) };
}
Matrix4f 
Matrix4f::operator*(Matrix4f& m)
{
  return { {
      a.x * m.a.x + a.y * m.b.x + a.z * m.c.x + a.w * m.d.x,
      a.x * m.a.y + a.y * m.b.y + a.z * m.c.y + a.w * m.d.y,
      a.x * m.a.z + a.y * m.b.z + a.z * m.c.z + a.w * m.d.z,
      a.x * m.a.w + a.y * m.b.w + a.z * m.c.w + a.w * m.d.w
      },{
      b.x * m.a.x + b.y * m.b.x + b.z * m.c.x + b.w * m.d.x,
      b.x * m.a.y + b.y * m.b.y + b.z * m.c.y + b.w * m.d.y,
      b.x * m.a.z + b.y * m.b.z + b.z * m.c.z + b.w * m.d.z,
      b.x * m.a.w + b.y * m.b.w + b.z * m.c.w + b.w * m.d.w
      },{
      c.x * m.a.x + c.y * m.b.x + c.z * m.c.x + c.w * m.d.x,
      c.x * m.a.y + c.y * m.b.y + c.z * m.c.y + c.w * m.d.y,
      c.x * m.a.z + c.y * m.b.z + c.z * m.c.z + c.w * m.d.z,
      c.x * m.a.w + c.y * m.b.w + c.z * m.c.w + c.w * m.d.w
      },{
      d.x * m.a.x + d.y * m.b.x + d.z * m.c.x + d.w * m.d.x,
      d.x * m.a.y + d.y * m.b.y + d.z * m.c.y + d.w * m.d.y,
      d.x * m.a.z + d.y * m.b.z + d.z * m.c.z + d.w * m.d.z,
      d.x * m.a.w + d.y * m.b.w + d.z * m.c.w + d.w * m.d.w
      } };
}
void 
Matrix4f::operator*=(Matrix4f& m)
{
  a = {
      a.x * m.a.x + a.y * m.b.x + a.z * m.c.x + a.w * m.d.x,
      a.x * m.a.y + a.y * m.b.y + a.z * m.c.y + a.w * m.d.y,
      a.x * m.a.z + a.y * m.b.z + a.z * m.c.z + a.w * m.d.z,
      a.x * m.a.w + a.y * m.b.w + a.z * m.c.w + a.w * m.d.w
  };
  b = {
      b.x * m.a.x + b.y * m.b.x + b.z * m.c.x + b.w * m.d.x,
      b.x * m.a.y + b.y * m.b.y + b.z * m.c.y + b.w * m.d.y,
      b.x * m.a.z + b.y * m.b.z + b.z * m.c.z + b.w * m.d.z,
      b.x * m.a.w + b.y * m.b.w + b.z * m.c.w + b.w * m.d.w
  };
  c = {
      c.x * m.a.x + c.y * m.b.x + c.z * m.c.x + c.w * m.d.x,
      c.x * m.a.y + c.y * m.b.y + c.z * m.c.y + c.w * m.d.y,
      c.x * m.a.z + c.y * m.b.z + c.z * m.c.z + c.w * m.d.z,
      c.x * m.a.w + c.y * m.b.w + c.z * m.c.w + c.w * m.d.w
  };
  d = {
      d.x * m.a.x + d.y * m.b.x + d.z * m.c.x + d.w * m.d.x,
      d.x * m.a.y + d.y * m.b.y + d.z * m.c.y + d.w * m.d.y,
      d.x * m.a.z + d.y * m.b.z + d.z * m.c.z + d.w * m.d.z,
      d.x * m.a.w + d.y * m.b.w + d.z * m.c.w + d.w * m.d.w
  };
}
void 
Matrix4f::transpose()
{
  swap(a.y, b.x);
  swap(a.z, c.x);
  swap(b.z, c.y);
  swap(a.w, d.x);
  swap(b.w, d.y);
  swap(c.w, d.z);
}
float 
Matrix4f::determinant()
{
  float ans = 0;
  Matrix3f tempMatrix;
  tempMatrix = { { b.x,b.y,b.z }, { c.x,c.y,c.z }, { d.x,d.y,d.z } };
  ans -= tempMatrix.determinant() * a.w;
  tempMatrix.a = { a.x,a.y,a.z };
  ans += tempMatrix.determinant() * b.w;
  tempMatrix.b = { b.x,b.y,b.z };
  ans -= tempMatrix.determinant() * c.w;
  tempMatrix.c = { c.x,c.y,c.z };
  ans += tempMatrix.determinant() * d.w;
  return ans;
}
float 
Matrix4f::minorDet(uint8 r1, uint8 r2, uint8 r3, uint8 c1, uint8 c2, uint8 c3)
{
  Matrix3f temp = { {vectors[r1][c1],vectors[r1][c2],vectors[r1][c3]},
  {vectors[r2][c1],vectors[r2][c2],vectors[r2][c3]},
  {vectors[r3][c1],vectors[r3][c2],vectors[r3][c3]} };
  return temp.determinant();
}
Matrix4f 
Matrix4f::inverse()
{
  float det = determinant();
  OA_ASSERT(det != 0);
  Matrix4f Adjugate = { { minorDet(1,2,3,1,2,3),-minorDet(0,2,3,1,2,3),minorDet(0,1,3,1,2,3),-minorDet(0,1,2,1,2,3) },
    { -minorDet(1,2,3,0,2,3),minorDet(0,2,3,0,2,3),-minorDet(0,1,3,0,2,3),minorDet(0,1,2,0,2,3) },
    { minorDet(1,2,3,0,1,3),-minorDet(0,2,3,0,1,3),minorDet(0,1,3,0,1,3),-minorDet(0,1,2,0,1,3) },
    { -minorDet(1,2,3,0,1,2),minorDet(0,2,3,0,1,2),-minorDet(0,1,3,0,1,2),minorDet(0,1,2,0,1,2) }, };
  return Adjugate * (1.f / det);
}
Matrix4f 
Matrix4f::translateMatrix(Vector3f& v)
{
  return Matrix4f({ 1.f,0.f,0.f,v.x },
                  { 0.f,1.f,0.f,v.y },
                  { 0.f,0.f,1.f,v.z },
                  { 0.f,0.f,0.f,1.f });
}
Matrix4f 
Matrix4f::scaleMatrix(Vector3f& v)
{
  return Matrix4f({ v.x,0.f,0.f,0.f },
                  { 0.f,v.y,0.f,0.f },
                  { 0.f,0.f,v.z,0.f },
                  { 0.f,0.f,0.f,1.f });
}
Matrix4f
Matrix4f::rotationMatrixZ(float r)
{
  float c = Math::cos(r);
  float s = Math::sin(r);
  return Matrix4f({ c,-s,0.f,0.f },
                  { s,c,0.f,0.f },
                  { 0.f,0.f,1.f,0.f },
                  { 0.f,0.f,0.f,1.f });
}
Matrix4f 
Matrix4f::rotationMatrixX(float r)
{
  float c = Math::cos(r);
  float s = Math::sin(r);
  return Matrix4f({ 1.f,0.f,0.f,0.f },
                  { 0.f,c,-s,0.f },
                  { 0.f,s,c,0.f },
                  { 0.f,0.f,0.f,1.f });
}
Matrix4f 
Matrix4f::rotationMatrixY(float r)
{
  float c = Math::cos(r);
  float s = Math::sin(r);
  return Matrix4f({ c,0.f,s,0.f },
                  { 0.f,1.f,0.f,0.f },
                  { -s,0.f,c,0.f },
                  { 0.f,0.f,0.f,1.f });
}
Matrix4f 
Matrix4f::rotationMatrix(float r, Vector3f& v)
{
  float c = Math::cos(r);
  float s = Math::sin(r);
  float mc = 1 - c;
  float xy = v.x * v.y * mc;
  float xz = v.x * v.z * mc;
  float yz = v.y * v.z * mc;
  float sx = s * v.x;
  float sy = s * v.y;
  float sz = s * v.z;
  return  Matrix4f({ c + mc * v.x * v.x,xy - sz , xz + sy,0.f },
                   { xz + sz ,c + mc * v.y * v.y,yz - sx,0.f },
                   { xz - sy,yz + sx,c + mc * v.y * v.y,0.f },
                   { 0.f,0.f,0.f,1.f });
}

bool OA_UTILITY_EXPORT 
operator==(Matrix4f m1, Matrix4f m2)
{
  return m1.a == m2.a && m1.b == m2.b && m1.c == m2.c;
}
}
