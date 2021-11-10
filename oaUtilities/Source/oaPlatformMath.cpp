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
#include "oaPlane.h"

namespace oaEngineSDK{

const float PlatformMath::PI = 3.1415926535897932384626433832795f;
const float PlatformMath::HALF_PI = 1.57079632679489661923132169163975f;
const float PlatformMath::TWO_PI = 6.283185307179586476925286766559f;
const float PlatformMath::INV_PI = 0.318309886183790671537767526745f;
const float PlatformMath::INV_TWO_PI = 0.159154943091895335768883763372f;
const float PlatformMath::RAD_TO_DEG = 57.2957795130823208767981548141f;
const float PlatformMath::DEG_TO_RAD = 0.01745329251994329576923690768f;
const float PlatformMath::MAX_FLOAT = FLT_MAX;

float
PlatformMath::invSqrt(float number)
{
  float x2 = number * 0.5f;
  int xi = *reinterpret_cast<int *>( &number );
  xi = 1597294787 - (xi >> 1);
  float y =  *reinterpret_cast<float *>( &xi );
  y  = y * ( 1.5f - ( x2 * y * y ) ); 
  return y;
}

bool 
PlatformMath::overlap(const Vector3f& _point, const Sphere& _sphere)
{
  return (_sphere.center - _point).magnitud() < _sphere.radius;
}

bool 
PlatformMath::overlap(const Sphere& _sphere1, const Sphere& _sphere2)
{
  return (_sphere1.center - _sphere2.center).magnitud()
    < _sphere1.radius+_sphere2.radius;
}

bool 
PlatformMath::overlap(const Vector3f& _point, const BoxAABB& _box)
{
  return _point.x> _box.minPoint.x && _point.x < _box.maxPoint.x &&
    _point.y> _box.minPoint.y && _point.y < _box.maxPoint.y &&
    _point.z> _box.minPoint.z && _point.z < _box.maxPoint.z;
}

bool 
PlatformMath::overlap(const Sphere& _sphere, const BoxAABB& _box)
{
  Vector3f point = 
  { max(_box.minPoint.x, min(_sphere.center.x, _box.maxPoint.x)),
    max(_box.minPoint.y, min(_sphere.center.y, _box.maxPoint.y)),
    max(_box.minPoint.z, min(_sphere.center.z, _box.maxPoint.z)) };

  return (point- _sphere.center).magnitud() < _sphere.radius;
}

bool 
PlatformMath::overlap(const BoxAABB& _box1, const BoxAABB& _box2)
{
  return 
    _box1.maxPoint.x > _box2.minPoint.x && 
    _box1.minPoint.x < _box2.maxPoint.x &&
    _box1.maxPoint.y > _box2.minPoint.y && 
    _box1.minPoint.y < _box2.maxPoint.y &&
    _box1.maxPoint.z > _box2.minPoint.z && 
    _box1.minPoint.z < _box2.maxPoint.z;
}

bool 
PlatformMath::overlap(const Vector3f& _point, const Capsule& _capsule)
{
  float height1 = _capsule.base.z+_capsule.radius;
  float height2 = _capsule.base.z+_capsule.height-_capsule.radius;
  return ((_point.xy - _capsule.base.xy).magnitud() < _capsule.radius 
          && _point.z > height1
          && _point.z < height2) 
  ||(Vector3f(_capsule.base.xy,height1) - _point).magnitud() < _capsule.radius 
  ||(Vector3f(_capsule.base.xy,height2) - _point).magnitud() < _capsule.radius;
}

bool 
PlatformMath::overlap(const Sphere& _sphere, const Capsule& _capsule)
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

bool 
PlatformMath::overlap(const BoxAABB& _box, const Capsule& _capsule)
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

bool 
PlatformMath::overlap(const Capsule& _capsule1, const Capsule& _capsule2)
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

float 
PlatformMath::distance(const Line& _line, const Vector3f& _point)
{
  Vector3f u = _point - _line.startingPoint;
  return Vector3f::cross(_line.direction,u).magnitud();
}

float 
PlatformMath::distance(const Line& _line1, const Line& _line2)
{
  auto dif = _line2.startingPoint - _line1.startingPoint;
  float v12 = Vector3f::dot(_line1.direction,_line1.direction);
  float v22 = Vector3f::dot(_line2.direction,_line2.direction);
  float v1v2 = Vector3f::dot(_line1.direction,_line2.direction);
  float det = v1v2 * v1v2 - v12 * v22;
  if (Math::abs(det) > FLT_MIN) {
    det = 1.f / det;
    float dpvl = Vector3f::dot(dif,_line1.direction);
    float dpv2 = Vector3f::dot(dif,_line2.direction);
    float t1 = (v1v2 * dpv2 - v22 * dpvl)* det;
    float t2 = (v12 * dpv2 - v1v2 * dpvl) * det;
    return (dif + _line2.direction * t2 - _line1.direction * t1).magnitud();
  }
  Vector3f a = Vector3f::cross(dif,_line1.direction);
  return (sqrt( Vector3f::dot(a,a) / v12));
}

float 
PlatformMath::distance(const Plane& _plane, const Vector3f& _point)
{
  return abs(Vector3f::dot(_plane.normal,_point)+_plane.d);
}

bool 
PlatformMath::intersect(const Plane& _plane, const Line& _line, Vector3f& _point)
{
  float fv = Vector3f::dot(_plane.normal,_line.direction);
  if (Math::abs(fv) > FLT_MIN) {
    _point = _line.startingPoint 
           - _line.direction 
           * ((Vector3f::dot(_plane.normal,_line.getStaringPoint())+_plane.d) / fv);
    return true;
  }
  return false;
}

bool 
PlatformMath::intersect(const Plane& _plane1, 
                             const Plane& _plane2, 
                             const Plane& _plane3, 
                             Vector3f& _point)
{
  Vector3f n =  Vector3f::cross(_plane1.normal,_plane2.normal);
  float det = Vector3f::dot(n,_plane3.normal);
  if (abs(det) > FLT_MIN) {
    _point = (Vector3f::cross(_plane3.normal,_plane2.normal) * _plane1.d 
            + Vector3f::cross(_plane1.normal,_plane3.normal) * _plane2.d 
            - n * _plane3.d) / det;
    return true;
  }
  return false;
}

bool 
PlatformMath::intersect(const Plane& _plane1, const Plane& _plane2, Line& _line)
{
  Vector3f dir = Vector3f::cross(_plane1.normal,_plane2.normal);
  _line.setDirection(dir);
  float det = Vector3f::dot(dir,dir);
  if (det > FLT_MIN) {
    _line.setStaringPoint((Vector3f::cross(dir,_plane1.normal) * _plane2.d + Vector3f::cross(dir,_plane2.normal) * _plane1.d) / det);
    return true;
  }
  return false;
}

}
