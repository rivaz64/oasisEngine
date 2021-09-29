/**
* @file oaPlatformMath.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/07/2021
*/

#include "oaPlatformMath.h"
#include "oaVector3f.h"
#include "oaSphere.h"
#include "oaBoxAABB.h"
#include "oaCapsule.h"
#include "oaLine.h"

namespace oaEngineSDK{

const float PlatformMath::PI = 3.1415926535897932384626433832795f;
const float PlatformMath::HALF_PI = 1.57079632679489661923132169163975f;
const float PlatformMath::TWO_PI = 6.283185307179586476925286766559f;
const float PlatformMath::INV_PI = 0.318309886183790671537767526745f;
const float PlatformMath::INV_TWO_PI = 0.159154943091895335768883763372f;
const float PlatformMath::RAD_TO_DEG = 57.2957795130823208767981548141f;
const float PlatformMath::DEG_TO_RAD = 0.01745329251994329576923690768f;

float OA_UTILITY_EXPORT PlatformMath::invSqrt(float number)
{
  long i;
  float x2, y;
  const float threehalfs = 1.5F;

  x2 = number * 0.5F;
  y = number;
  i = *(long*)&y;
  i = 0x5f3759df - (i >> 1);
  y = *(float*)&i;
  y = y * (threehalfs - (x2 * y * y));
  y = y * (threehalfs - (x2 * y * y));
  y = y * (threehalfs - (x2 * y * y));
  return y;
}

bool PlatformMath::overlap(const Vector3f& _point, const Sphere& _sphere)
{
  return (_sphere.center - _point).magnitud() < _sphere.radius;
}

bool PlatformMath::overlap(const Sphere& _sphere1, const Sphere& _sphere2)
{
  return (_sphere1.center - _sphere2.center).magnitud()
    < _sphere1.radius+_sphere2.radius;
}

bool PlatformMath::overlap(const Vector3f& _point, const BoxAABB& _box)
{
  return _point.x> _box.minPoint.x && _point.x < _box.maxPoint.x &&
    _point.y> _box.minPoint.y && _point.y < _box.maxPoint.y &&
    _point.z> _box.minPoint.z && _point.z < _box.maxPoint.z;
}

bool PlatformMath::overlap(const Sphere& _sphere, const BoxAABB& _box)
{
  Vector3f point = 
  { max(_box.minPoint.x, min(_sphere.center.x, _box.maxPoint.x)),
    max(_box.minPoint.y, min(_sphere.center.y, _box.maxPoint.y)),
    max(_box.minPoint.z, min(_sphere.center.z, _box.maxPoint.z)) };

  return (point- _sphere.center).magnitud() < _sphere.radius;
}

bool PlatformMath::overlap(const BoxAABB& _box1, const BoxAABB& _box2)
{
  return 
    _box1.maxPoint.x > _box2.minPoint.x && 
    _box1.minPoint.x < _box2.maxPoint.x &&
    _box1.maxPoint.y > _box2.minPoint.y && 
    _box1.minPoint.y < _box2.maxPoint.y &&
    _box1.maxPoint.z > _box2.minPoint.z && 
    _box1.minPoint.z < _box2.maxPoint.z;
}

bool PlatformMath::overlap(const Vector3f& _point, const Capsule& _capsule)
{
  float height1 = _capsule.base.z+_capsule.radius;
  float height2 = _capsule.base.z+_capsule.height-_capsule.radius;
  return ((_point.xy - _capsule.base.xy).magnitud() < _capsule.radius 
          && _point.z > height1
          && _point.z < height2) 
  ||(Vector3f(_capsule.base.xy,height1) - _point).magnitud() < _capsule.radius 
  ||(Vector3f(_capsule.base.xy,height2) - _point).magnitud() < _capsule.radius;
}

bool PlatformMath::overlap(const Sphere& _sphere, const Capsule& _capsule)
{
  float height1 = _capsule.base.z+_capsule.radius;
  float height2 = _capsule.base.z+_capsule.height-_capsule.radius;
  float radius = _capsule.radius + _sphere.radius;
  return ((_sphere.center.xy - _capsule.base.xy).magnitud() < radius
          && _sphere.center.z > height1
          && _sphere.center.z < height2) 
  ||(Vector3f(_capsule.base.xy,height1) - _sphere.center).magnitud() < radius
  ||(Vector3f(_capsule.base.xy,height2) - _sphere.center).magnitud() < radius;
}

bool PlatformMath::overlap(const BoxAABB& _box, const Capsule& _capsule)
{
  Vector2f point = 
  { Math::max(_box.minPoint.x, Math::min(_capsule.base.x, _box.maxPoint.x)),
    Math::max(_box.minPoint.y, Math::min(_capsule.base.y, _box.maxPoint.y))};

  if ((point- _capsule.base.xy).magnitud() < _capsule.radius){
    return true;
  }
  Sphere s1(Vector3f(_capsule.base.xy,
            _capsule.base.z+_capsule.radius),_capsule.radius);
  Sphere s2(Vector3f(_capsule.base.xy,
            _capsule.base.z+_capsule.height-_capsule.radius),_capsule.radius);
  return overlap(s1,_box) || overlap(s2,_box);
}

bool PlatformMath::overlap(const Capsule& _capsule1, const Capsule& _capsule2)
{
  float height11 = _capsule1.base.z+_capsule1.radius;
  float height21 = _capsule1.base.z+_capsule1.height-_capsule1.radius;
  float height12 = _capsule2.base.z+_capsule2.radius;
  float height22 = _capsule2.base.z+_capsule2.height-_capsule1.radius;
  if((_capsule1.base.xy-_capsule2.base.xy).magnitud()
     < _capsule1.radius+_capsule2.radius
     && height11<height22 && height21 > height12)
  {
    return true;
  }
  Sphere s11(Vector3f(_capsule1.base.xy,
            _capsule1.base.z+_capsule1.radius),_capsule1.radius);
  Sphere s21(Vector3f(_capsule1.base.xy,
            _capsule1.base.z+_capsule1.height-_capsule1.radius),_capsule1.radius);
  Sphere s12(Vector3f(_capsule2.base.xy,
             _capsule2.base.z+_capsule2.radius),_capsule2.radius);
  Sphere s22(Vector3f(_capsule2.base.xy,
             _capsule2.base.z+_capsule2.height-_capsule2.radius),_capsule2.radius);

  return overlap(s11,s22) || overlap(s12,s21);
}

float PlatformMath::distance(const Line& _line, const Vector3f& _point)
{
  Vector3f u = _point - _line.startingPoint;
  return Vector3f::cross(_line.direction,u).magnitud();
}

}
