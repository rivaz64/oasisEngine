#include "oaQuaternion.h"
namespace oaEngineSDK {
Quaternion oaEngineSDK::Quaternion::operator+(Quaternion& q)
{
  return { r + q.r,i+q.i,j+q.j,k+q.k };
}
void Quaternion::operator+=(Quaternion& q)
{
  r += q.r;
  i += q.i;
  j += q.j;
  k += q.k;
}
Quaternion Quaternion::operator-(Quaternion& q)
{
  return { r - q.r,i - q.i,j - q.j,k - q.k };
}
void Quaternion::operator-=(Quaternion& q)
{
  r -= q.r;
  i -= q.i;
  j -= q.j;
  k -= q.k;
}
Quaternion Quaternion::operator*(Quaternion& q)
{
  return { };
}
void Quaternion::operator*=(Quaternion& q)
{
  r=r* q.r - i * q.i - j * q.j - k * q.k,
  i=i* q.r + j * q.k - k * q.j + r * q.i,
  j=j* q.r + k * q.i + r * q.j - i * q.k,
  k=k* q.r + r * q.k + i * q.j - j * q.i
}
}

