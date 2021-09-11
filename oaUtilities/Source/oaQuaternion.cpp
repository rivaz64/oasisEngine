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
  return { r * q.r - i * q.i - j * q.j - k * q.k,
           i * q.r + j * q.k - k * q.j + r * q.i,
           j * q.r + k * q.i + r * q.j - i * q.k,
           k * q.r + r * q.k + i * q.j - j * q.i,};
}
void Quaternion::operator*=(Quaternion& q)
{
  r = r * q.r - i * q.i - j * q.j - k * q.k;
  i = i * q.r + j * q.k - k * q.j + r * q.i;
  j = j * q.r + k * q.i + r * q.j - i * q.k;
  k = k * q.r + r * q.k + i * q.j - j * q.i;
}
Quaternion Quaternion::conjugate()
{
  return { r,-i,-j,-k };
}
Quaternion Quaternion::inverse()
{
  float absVal = r * r + i * i + j * j + k * k;
  return { r / absVal,-i / absVal,-j / absVal,-k / absVal };
}
Quaternion Quaternion::normal()
{
  float absVal = r * r + i * i + j * j + k * k;
  return { r / absVal,i / absVal,j / absVal,k / absVal };
}
bool OA_UTILITY_EXPORT operator==(Quaternion q1, Quaternion q2)
{
  return q1.r==q2.r&& q1.i == q2.i&& q1.j == q2.j&& q1.k == q2.k;
}
}

