/**
 * @file oaMatrix4f.cpp
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */


#include "oaMatrix4f.h"
#include "oaVector3f.h"
#include "oaVector4f.h"
#include "oaMatrix3f.h"

namespace oaEngineSDK {

Matrix4f::Matrix4f(const Matrix3f& m)  :
  row1(m.row1,0), row2(m.row2,0), row3(m.row3,0), row4(0,0,0,0) 
{
}

bool const
Matrix4f::operator==(const Matrix4f& m) const
{
  return
    row1 == m.row1 &&
    row2 == m.row2 &&
    row3 == m.row3 &&
    row4 == m.row4;
}

Matrix4f
Matrix4f::operator+(const Matrix4f& m) const
{
  return Matrix4f(row1+m.row1, row2+m.row2, row3+m.row3, row4+m.row4);
}

Matrix4f&
Matrix4f::operator+=(const Matrix4f& m)
{
  row1 += m.row1;
  row2 += m.row2;
  row3 += m.row3;
  row4 += m.row4;
  return *this;
}

Matrix4f
Matrix4f::operator-(const Matrix4f& m) const
{
  return Matrix4f(row1-m.row1, row2-m.row2, row3-m.row3, row3-m.row3);
}

Matrix4f&
Matrix4f::operator-=(const Matrix4f& m)
{
  row1 -= m.row1;
  row2 -= m.row2;
  row3 -= m.row3;
  row4 -= m.row4;
  return *this;
}

Matrix4f
Matrix4f::operator*(const float m) const
{
   return Matrix4f(row1*m, row2*m, row3*m, row4*m);
}

Matrix4f&
Matrix4f::operator*=(float m)
{
  row1 *= m;
  row2 *= m;
  row3 *= m;
  row4 *= m;
  return *this;
}
Vector4f
Matrix4f::operator*(const Vector4f& v) const
{
  //auto mat = this->transposed();
  //return Vector4f(mat.row1.dot(v),mat.row2.dot(v),mat.row3.dot(v),mat.row4.dot(v));
  return Vector4f(row1.dot(v),row2.dot(v),row3.dot(v),row4.dot(v));
}
Matrix4f
Matrix4f::operator*(const Matrix4f& m) const
{
  return Matrix4f(
    Vector4f(row1.x * m.row1.x + row1.y * m.row2.x + row1.z * m.row3.x + row1.w * m.row4.x,
             row1.x * m.row1.y + row1.y * m.row2.y + row1.z * m.row3.y + row1.w * m.row4.y,
             row1.x * m.row1.z + row1.y * m.row2.z + row1.z * m.row3.z + row1.w * m.row4.z,
             row1.x * m.row1.w + row1.y * m.row2.w + row1.z * m.row3.w + row1.w * m.row4.w),
    Vector4f(row2.x * m.row1.x + row2.y * m.row2.x + row2.z * m.row3.x + row2.w * m.row4.x,
             row2.x * m.row1.y + row2.y * m.row2.y + row2.z * m.row3.y + row2.w * m.row4.y,
             row2.x * m.row1.z + row2.y * m.row2.z + row2.z * m.row3.z + row2.w * m.row4.z,
             row2.x * m.row1.w + row2.y * m.row2.w + row2.z * m.row3.w + row2.w * m.row4.w),
    Vector4f(row3.x * m.row1.x + row3.y * m.row2.x + row3.z * m.row3.x + row3.w * m.row4.x,
             row3.x * m.row1.y + row3.y * m.row2.y + row3.z * m.row3.y + row3.w * m.row4.y,
             row3.x * m.row1.z + row3.y * m.row2.z + row3.z * m.row3.z + row3.w * m.row4.z,
             row3.x * m.row1.w + row3.y * m.row2.w + row3.z * m.row3.w + row3.w * m.row4.w),
    Vector4f(row4.x * m.row1.x + row4.y * m.row2.x + row4.z * m.row3.x + row4.w * m.row4.x,
             row4.x * m.row1.y + row4.y * m.row2.y + row4.z * m.row3.y + row4.w * m.row4.y,
             row4.x * m.row1.z + row4.y * m.row2.z + row4.z * m.row3.z + row4.w * m.row4.z,
             row4.x * m.row1.w + row4.y * m.row2.w + row4.z * m.row3.w + row4.w * m.row4.w)
  );
}

Matrix4f&
Matrix4f::operator*=(const Matrix4f& m)
{
  row1.x = row1.x * m.row1.x + row1.y * m.row2.x + row1.z * m.row3.x + row1.w * m.row4.x;
  row1.y = row1.x * m.row1.y + row1.y * m.row2.y + row1.z * m.row3.y + row1.w * m.row4.y;
  row1.w = row1.x * m.row1.z + row1.y * m.row2.z + row1.z * m.row3.z + row1.w * m.row4.z;
  row1.z = row1.x * m.row1.w + row1.y * m.row2.w + row1.z * m.row3.w + row1.w * m.row4.w;
  row2.x = row2.x * m.row1.x + row2.y * m.row2.x + row2.z * m.row3.x + row2.w * m.row4.x;
  row2.y = row2.x * m.row1.y + row2.y * m.row2.y + row2.z * m.row3.y + row2.w * m.row4.y;
  row2.w = row2.x * m.row1.z + row2.y * m.row2.z + row2.z * m.row3.z + row2.w * m.row4.z;
  row2.z = row2.x * m.row1.w + row2.y * m.row2.w + row2.z * m.row3.w + row2.w * m.row4.w;
  row3.x = row3.x * m.row1.x + row3.y * m.row2.x + row3.z * m.row3.x + row3.w * m.row4.x;
  row3.y = row3.x * m.row1.y + row3.y * m.row2.y + row3.z * m.row3.y + row3.w * m.row4.y;
  row3.w = row3.x * m.row1.z + row3.y * m.row2.z + row3.z * m.row3.z + row3.w * m.row4.z;
  row3.z = row3.x * m.row1.w + row3.y * m.row2.w + row3.z * m.row3.w + row3.w * m.row4.w;
  row4.x = row4.x * m.row1.x + row4.y * m.row2.x + row4.z * m.row3.x + row4.w * m.row4.x;
  row4.y = row4.x * m.row1.y + row4.y * m.row2.y + row4.z * m.row3.y + row4.w * m.row4.y;
  row4.w = row4.x * m.row1.z + row4.y * m.row2.z + row4.z * m.row3.z + row4.w * m.row4.z;
  row4.z = row4.x * m.row1.w + row4.y * m.row2.w + row4.z * m.row3.w + row4.w * m.row4.w;
  return *this;
}

Matrix3f 
Matrix4f::toMatrix3f() const
{
  return Matrix3f(row1.xyz,row2.xyz,row3.xyz);
}

void
Matrix4f::transpose()
{
  swap(row1.y, row2.x);
  swap(row1.z, row3.x);
  swap(row1.w, row4.x);
  swap(row2.z, row3.y);
  swap(row2.w, row4.y);
  swap(row3.w, row4.z);
}

Matrix4f
Matrix4f::transposed() const
{
  Matrix4f ans = *this;
  ans.transpose();
  return ans;
}

float
Matrix4f::determinant() const
{
  float ans = 0;
  Matrix3f tempMatrix = toMatrix3f();
  ans -= tempMatrix.determinant() * row4.w;
  tempMatrix.row3 = row4.xyz;
  ans += tempMatrix.determinant() * row3.w;
  tempMatrix.row2 = row3.xyz;
  ans -= tempMatrix.determinant() * row2.w;
  tempMatrix.row1 = row2.xyz;
  ans += tempMatrix.determinant() * row1.w;
  return ans;
}

Matrix4f
Matrix4f::inverse() const 
{
  float a3434 = row3.z * row4.w - row3.w * row4.z;
  float a2434 = row3.y * row4.w - row3.w * row4.y;
  float a2334 = row3.y * row4.z - row3.z * row4.y;
  float a1434 = row3.x * row4.w - row3.w * row4.x;
  float a1334 = row3.x * row4.z - row3.z * row4.x;
  float a1234 = row3.x * row4.y - row3.y * row4.x;
  float a3424 = row2.z * row4.w - row2.w * row4.z;
  float a2424 = row2.y * row4.w - row2.w * row4.y;
  float a2324 = row2.y * row4.z - row2.z * row4.y;
  float a3423 = row2.z * row3.w - row2.w * row3.z;
  float a2423 = row2.y * row3.w - row2.w * row3.y;
  float a2323 = row2.y * row3.z - row2.z * row3.y;
  float a1424 = row2.x * row4.w - row2.w * row4.x;
  float a1324 = row2.x * row4.z - row2.z * row4.x;
  float a1423 = row2.x * row3.w - row2.w * row3.x;
  float a1323 = row2.x * row3.z - row2.z * row3.x;
  float a1224 = row2.x * row4.x - row2.y * row4.x;
  float a1223 = row2.x * row3.x - row2.y * row3.x;

  float det = row1.x * (row2.y * a3434 - row2.z * a2434 + row2.w * a2334)
            - row1.y * (row2.x * a3434 - row2.z * a1434 + row2.w * a1334)
            + row1.z * (row2.x * a2434 - row2.y * a1434 + row2.w * a1234)
            - row1.w * (row2.x * a2334 - row2.y * a1334 + row2.z * a1234);
  float invDet = 1.f / det;

  Matrix4f inv = Matrix4f(
    Vector4f(+(row2.y * a3434 - row2.z * a2434 + row2.w * a2334),
             -(row2.x * a3434 - row2.z * a1434 + row2.w * a1334),
             +(row2.x * a2434 - row2.y * a1434 + row2.w * a1234),
             -(row2.x * a2334 - row2.y * a1334 + row2.z * a1234)),
    Vector4f(-(row1.y * a3434 - row1.z * a2434 + row1.w * a2334),
             +(row1.x * a3434 - row1.z * a1434 + row1.w * a1334),
             -(row1.x * a2434 - row1.y * a1434 + row1.w * a1234),
             +(row1.x * a2334 - row1.y * a1334 + row1.z * a1234)),
    Vector4f(+(row1.y * a3424 - row1.z * a2424 + row1.w * a2324),
             -(row1.x * a3424 - row1.z * a1424 + row1.w * a1324),
             +(row1.x * a2424 - row1.y * a1424 + row1.w * a1224),
             -(row1.x * a2324 - row1.y * a1324 + row1.z * a1224)),
    Vector4f(-(row1.y * a3423 - row1.z * a2423 + row1.w * a2323),
             +(row1.x * a3423 - row1.z * a1423 + row1.w * a1323),
             -(row1.x * a2423 - row1.y * a1423 + row1.w * a1223),
             +(row1.x * a2323 - row1.y * a1323 + row1.z * a1223)));
  return inv * invDet;
}

void 
Matrix4f::invert() 
{
  float a3434 = row3.z * row4.w - row3.w * row4.z;
  float a2434 = row3.y * row4.w - row3.w * row4.y;
  float a2334 = row3.y * row4.z - row3.z * row4.y;
  float a1434 = row3.x * row4.w - row3.w * row4.x;
  float a1334 = row3.x * row4.z - row3.z * row4.x;
  float a1234 = row3.x * row4.y - row3.y * row4.x;
  float a3424 = row2.z * row4.w - row2.w * row4.z;
  float a2424 = row2.y * row4.w - row2.w * row4.y;
  float a2324 = row2.y * row4.z - row2.z * row4.y;
  float a3423 = row2.z * row3.w - row2.w * row3.z;
  float a2423 = row2.y * row3.w - row2.w * row3.y;
  float a2323 = row2.y * row3.z - row2.z * row3.y;
  float a1424 = row2.x * row4.w - row2.w * row4.x;
  float a1324 = row2.x * row4.z - row2.z * row4.x;
  float a1423 = row2.x * row3.w - row2.w * row3.x;
  float a1323 = row2.x * row3.z - row2.z * row3.x;
  float a1224 = row2.x * row4.x - row2.y * row4.x;
  float a1223 = row2.x * row3.x - row2.y * row3.x;

  float det = row1.x * (row2.y * a3434 - row2.z * a2434 + row2.w * a2334)
            - row1.y * (row2.x * a3434 - row2.z * a1434 + row2.w * a1334)
            + row1.z * (row2.x * a2434 - row2.y * a1434 + row2.w * a1234)
            - row1.w * (row2.x * a2334 - row2.y * a1334 + row2.z * a1234);
  float invDet = 1.f / det;

  row1.x = +(row2.y * a3434 - row2.z * a2434 + row2.w * a2334);
  row1.y = -(row2.x * a3434 - row2.z * a1434 + row2.w * a1334);
  row1.z = +(row2.x * a2434 - row2.y * a1434 + row2.w * a1234);
  row1.w = -(row2.x * a2334 - row2.y * a1334 + row2.z * a1234);
  row2.x = -(row1.y * a3434 - row1.z * a2434 + row1.w * a2334);
  row2.y = +(row1.x * a3434 - row1.z * a1434 + row1.w * a1334);
  row2.z = -(row1.x * a2434 - row1.y * a1434 + row1.w * a1234);
  row2.w = +(row1.x * a2334 - row1.y * a1334 + row1.z * a1234);
  row3.x = +(row1.y * a3424 - row1.z * a2424 + row1.w * a2324);
  row3.y = -(row1.x * a3424 - row1.z * a1424 + row1.w * a1324);
  row3.z = +(row1.x * a2424 - row1.y * a1424 + row1.w * a1224);
  row3.w = -(row1.x * a2324 - row1.y * a1324 + row1.z * a1224);
  row4.x = -(row1.y * a3423 - row1.z * a2423 + row1.w * a2323);
  row4.y = +(row1.x * a3423 - row1.z * a1423 + row1.w * a1323);
  row4.z = -(row1.x * a2423 - row1.y * a1423 + row1.w * a1223);
  row4.w = +(row1.x * a2323 - row1.y * a1323 + row1.z * a1223);

  *this *= invDet;
}

Matrix4f
Matrix4f::translateMatrix(const Vector3f& v)
{
  return Matrix4f(
    Vector4f(1.f,0.f,0.f,v.x),
    Vector4f(0.f,1.f,0.f,v.y),
    Vector4f(0.f,0.f,1.f,v.z),
    Vector4f(0.f,0.f,0.f,1.f)
  );
}

Matrix4f 
Matrix4f::scaleMatrix(const Vector3f& v)
{
  return Matrix4f(
    Vector4f(v.x,0.f,0.f,0.f),
    Vector4f(0.f,v.y,0.f,0.f),
    Vector4f(0.f,0.f,v.z,0.f),
    Vector4f(0.f,0.f,0.f,1.f)
  );
}

Matrix4f
Matrix4f::rotationMatrixZ(const float r)
{
  float c = Math::cos(r);
  float s = Math::sin(r);
  return Matrix4f(
    Vector4f(  c, -s,0.f,0.f),
    Vector4f(  s,  c,0.f,0.f),
    Vector4f(0.f,0.f,1.f,0.f),
    Vector4f(0.f,0.f,0.f,1.f)
  );
}

Matrix4f 
Matrix4f::rotationMatrixX(const float r)
{
  float c = Math::cos(r);
  float s = Math::sin(r);
  return Matrix4f(
    Vector4f(1.f,0.f,0.f,0.f),
    Vector4f(0.f,  c, -s,0.f),
    Vector4f(0.f,  s,  c,0.f),
    Vector4f(0.f,0.f,0.f,1.f)
  );
}

Matrix4f 
Matrix4f::rotationMatrixY(const float r)
{
  float c = Math::cos(r);
  float s = Math::sin(r);
  return Matrix4f(
    Vector4f(  c,0.f,  s,0.f),
    Vector4f(0.f,1.f,0.f,0.f),
    Vector4f( -s,0.f,  c,0.f),
    Vector4f(0.f,0.f,0.f,1.f)
  );
}

Matrix4f 
Matrix4f::rotationMatrix(float r,const Vector3f& v)
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
  return  Matrix4f(
    Vector4f(c + mc * v.x * v.x, xy - sz           , xz + sy           , 0.f),
    Vector4f(xz + sz           , c + mc * v.y * v.y, yz - sx           , 0.f),
    Vector4f(xz - sy           , yz + sx           , c + mc * v.y * v.y, 0.f),
    Vector4f(0.f               , 0.f               , 0.f               , 1.f)
  );
}

Matrix4f Matrix4f::rotationMatrix(const Vector3f& v)
{
  float sx = Math::sin(v.x);
  float cx = Math::cos(v.x);
  float sy = Math::sin(v.y);
  float cy = Math::cos(v.y);
  float sz = Math::sin(v.z);
  float cz = Math::cos(v.z);
  return Matrix4f(
    Vector4f(cz*cy, cz*sy*sx-sz*cx, cz*sy*cx+sz*sx, 0.0f),
    Vector4f(sz*cy, sz*sy*sx+cz*cx, sz*sy*cx-cz*sx, 0.0f),
    Vector4f(-sy  , cy*sx         , cy*cx         , 0.0f),
    Vector4f(0.0f , 0.0f          , 0.0f          , 1.0f)
  );
}

const Matrix4f Matrix4f::IDENTITY = Matrix4f(
  Vector4f(1.0f,0.0f,0.0f,0.0f),
  Vector4f(0.0f,1.0f,0.0f,0.0f),
  Vector4f(0.0f,0.0f,1.0f,0.0f),
  Vector4f(0.0f,0.0f,0.0f,1.0f)
);

}
