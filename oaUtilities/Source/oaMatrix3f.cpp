/**
 * @file oaMatrix3f.cpp
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */


#include "oaMatrix3f.h"
#include"oaVector2f.h"
#include"oaVector3f.h"

namespace oaEngineSDK {

bool const
Matrix3f::operator==(const Matrix3f& m) const
{
  return
    row1 == m.row1 &&
    row2 == m.row2 &&
    row3 == m.row3;
}

Matrix3f
Matrix3f::operator+(const Matrix3f& m) const
{
  return Matrix3f(row1+m.row1, row2+m.row2, row3+m.row3);
}

Matrix3f&
Matrix3f::operator+=(const Matrix3f& m)
{
  row1 += m.row1;
  row2 += m.row2;
  row3 += m.row3;
  return *this;
}

Matrix3f
Matrix3f::operator-(const Matrix3f& m) const
{
  return Matrix3f(row1-m.row1, row2-m.row2, row3-m.row3);
}

Matrix3f&
Matrix3f::operator-=(const Matrix3f& m)
{
  row1 -= m.row1;
  row2 -= m.row2;
  row3 -= m.row3;
  return *this;
}

Matrix3f
Matrix3f::operator*(float m) const
{
  return Matrix3f(row1*m, row2*m, row3*m);
}

Matrix3f&
Matrix3f::operator*=(float m)
{
  row1 *= m;
  row2 *= m;
  row3 *= m;
  return *this;
}

Vector3f
Matrix3f::operator*(const Vector3f& v) const
{
  return Vector3f(row1.dot(v),row2.dot(v),row3.dot(v));
}

Matrix3f
Matrix3f::operator*(const Matrix3f& m) const
{
  return Matrix3f(
    Vector3f(row1.x* m.row1.x + row1.y * m.row2.x + row1.z * m.row3.x,
             row1.x* m.row1.y + row1.y * m.row2.y + row1.z * m.row3.y,
             row1.x* m.row1.z + row1.y * m.row2.z + row1.z * m.row3.z),
    Vector3f(row2.x* m.row1.x + row2.y * m.row2.x + row2.z * m.row3.x,
             row2.x* m.row1.y + row2.y * m.row2.y + row2.z * m.row3.y,
             row2.x* m.row1.z + row2.y * m.row2.z + row2.z * m.row3.z),
    Vector3f(row3.x* m.row1.x + row3.y * m.row2.x + row3.z * m.row3.x,
             row3.x* m.row1.y + row3.y * m.row2.y + row3.z * m.row3.y,
             row3.x* m.row1.z + row3.y * m.row2.z + row3.z * m.row3.z)
  );
}

Matrix3f&
Matrix3f::operator*=(const Matrix3f& m)
{
  row1.x = row1.x* m.row1.x + row1.y * m.row2.x + row1.z * m.row3.x;
  row1.y = row1.x* m.row1.y + row1.y * m.row2.y + row1.z * m.row3.y;
  row1.z = row1.x* m.row1.z + row1.y * m.row2.z + row1.z * m.row3.z;
  row2.x = row2.x* m.row1.x + row2.y * m.row2.x + row2.z * m.row3.x;
  row2.y = row2.x* m.row1.y + row2.y * m.row2.y + row2.z * m.row3.y;
  row2.z = row2.x* m.row1.z + row2.y * m.row2.z + row2.z * m.row3.z;
  row3.x = row3.x* m.row1.x + row3.y * m.row2.x + row3.z * m.row3.x;
  row3.y = row3.x* m.row1.y + row3.y * m.row2.y + row3.z * m.row3.y;
  row3.z = row3.x* m.row1.z + row3.y * m.row2.z + row3.z * m.row3.z;
  return *this;
}
void
Matrix3f::transpose()
{
  swap(row1.y, row2.x);
  swap(row1.z, row3.x);
  swap(row2.z, row3.y);
}
float
Matrix3f::determinant() const
{
  return row1.x * row2.y * row3.z + row1.y * row2.z * row3.x + row1.z * row2.x * row3.y
    - row1.z * row2.y * row3.x - row1.y * row2.x * row3.z - row1.x * row2.z * row3.y;
}

Matrix3f
Matrix3f::inverse() const
{
  float invDet = 1.f / determinant();
  return Matrix3f(                                                                                    
    Vector3f(+(row2.y * row3.z - row3.y * row2.z),-(row1.y * row3.z - row3.y * row1.z),+(row1.y * row2.z - row2.y * row1.z)),
    Vector3f(-(row2.x * row3.z - row3.x * row2.z),+(row1.x * row3.z - row3.x * row1.z),-(row1.x * row2.z - row2.x * row1.z)),
    Vector3f(+(row2.x * row3.y - row3.x * row2.y),-(row1.x * row3.y - row3.x * row1.y),+(row1.x * row2.y - row2.x * row1.y))
  )*invDet;
}

void 
Matrix3f::invert()
{
  float invDet = 1.f / determinant();
  row1.x = +(row2.y * row3.z - row3.y * row2.z);
  row1.y = -(row1.y * row3.z - row3.y * row1.z);
  row1.z = +(row1.y * row2.z - row2.y * row1.z);
  row2.x = -(row2.x * row3.z - row3.x * row2.z);
  row2.y = +(row1.x * row3.z - row3.x * row1.z);
  row2.z = -(row1.x * row2.z - row2.x * row1.z);
  row3.x = +(row2.x * row3.y - row3.x * row2.y);
  row3.y = -(row1.x * row3.y - row3.x * row1.y);
  row3.z = +(row1.x * row2.y - row2.x * row1.y);
  *this *= invDet;
}

Matrix3f
Matrix3f::translateMatrix(const Vector2f& v)
{
  return Matrix3f( Vector3f(1.f,0.f,v.x) ,
                   Vector3f(0.f,1.f,v.y) ,
                   Vector3f(0.f,0.f,1.f) );
}

Matrix3f
Matrix3f::scaleMatrix(const Vector2f& v)
{
  return Matrix3f( Vector3f(v.x,0.f,0.f) ,
                   Vector3f(0.f,v.y,0.f) ,
                   Vector3f(0.f,0.f,1.f) );
}

Matrix3f
Matrix3f::rotationMatrix(float r)
{
  float c = Math::cos(r);
  float s = Math::sin(r);
  return  Matrix3f(  Vector3f(c,-s,0.f   ),
                     Vector3f(s, -c, 0.f ), 
                     Vector3f(0.f,0.f,1.f));
}

}

