/**
* @file oaPlatformMath.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/07/2021
*/

#include "oaPlatformMath.h"
#include "oaVector3f.h"
#include "oaSphere.h"
#include "oaAABB.h"
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
  return (_sphere.getCenter() - _point).magnitud() < _sphere.getRadius();
}

bool 
PlatformMath::overlap(const Sphere& _sphere1, const Sphere& _sphere2)
{
  return (_sphere1.getCenter() - _sphere2.getCenter()).magnitud()
    < _sphere1.getRadius()+_sphere2.getRadius();
}

bool 
PlatformMath::overlap(const Vector3f& _point, const AABB& _box)
{
  return _point.x> _box.getMinPoint().x && _point.x < _box.getMaxPoint().x &&
    _point.y> _box.getMinPoint().y && _point.y < _box.getMaxPoint().y &&
    _point.z> _box.getMinPoint().z && _point.z < _box.getMaxPoint().z;
}

bool 
PlatformMath::overlap(const Sphere& _sphere, const AABB& _box)
{
  Vector3f point = 
  { max(_box.getMinPoint().x, min(_sphere.getCenter().x, _box.getMaxPoint().x)),
    max(_box.getMinPoint().y, min(_sphere.getCenter().y, _box.getMaxPoint().y)),
    max(_box.getMinPoint().z, min(_sphere.getCenter().z, _box.getMaxPoint().z)) };

  return (point- _sphere.getCenter()).magnitud() < _sphere.getRadius();
}

bool 
PlatformMath::overlap(const AABB& _box1, const AABB& _box2)
{
  return 
    _box1.getMaxPoint().x > _box2.getMinPoint().x && 
    _box1.getMinPoint().x < _box2.getMaxPoint().x &&
    _box1.getMaxPoint().y > _box2.getMinPoint().y && 
    _box1.getMinPoint().y < _box2.getMaxPoint().y &&
    _box1.getMaxPoint().z > _box2.getMinPoint().z && 
    _box1.getMinPoint().z < _box2.getMaxPoint().z;
}

bool 
PlatformMath::overlap(const Vector3f& _point, const Capsule& _capsule)
{
  float height1 = _capsule.getBase().z+_capsule.getRadius();
  float height2 = _capsule.getBase().z+_capsule.getHeight()-_capsule.getRadius();
  return ((_point.xy - _capsule.getBase().xy).magnitud() < _capsule.getRadius() 
          && _point.z > height1
          && _point.z < height2) 
  ||(Vector3f(_capsule.getBase().xy,height1) - _point).magnitud() < _capsule.getRadius() 
  ||(Vector3f(_capsule.getBase().xy,height2) - _point).magnitud() < _capsule.getRadius();
}

bool 
PlatformMath::overlap(const Sphere& _sphere, const Capsule& _capsule)
{
  float height1 = _capsule.getBase().z+_capsule.getRadius();
  float height2 = _capsule.getBase().z+_capsule.getHeight()-_capsule.getRadius();
  float radius = _capsule.getRadius() + _sphere.getRadius();
  return ((_sphere.getCenter().xy - _capsule.getBase().xy).magnitud() < radius
          && _sphere.getCenter().z > height1
          && _sphere.getCenter().z < height2) 
  ||(Vector3f(_capsule.getBase().xy,height1) - _sphere.getCenter()).magnitud() < radius
  ||(Vector3f(_capsule.getBase().xy,height2) - _sphere.getCenter()).magnitud() < radius;
}

bool 
PlatformMath::overlap(const AABB& _box, const Capsule& _capsule)
{
  Vector2f point = 
  { Math::max(_box.getMinPoint().x, Math::min(_capsule.getBase().x, _box.getMaxPoint().x)),
    Math::max(_box.getMinPoint().y, Math::min(_capsule.getBase().y, _box.getMaxPoint().y))};

  if ((point- _capsule.getBase().xy).magnitud() < _capsule.getRadius()){
    return true;
  }
  Sphere s1(Vector3f(_capsule.getBase().xy,
            _capsule.getBase().z+_capsule.getRadius()),_capsule.getRadius());
  Sphere s2(Vector3f(_capsule.getBase().xy,
            _capsule.getBase().z+_capsule.getHeight()-_capsule.getRadius()),_capsule.getRadius());
  return overlap(s1,_box) || overlap(s2,_box);
}

bool 
PlatformMath::overlap(const Capsule& _capsule1, const Capsule& _capsule2)
{
  float height11 = _capsule1.getBase().z+_capsule1.getRadius();
  float height21 = _capsule1.getBase().z+_capsule1.getHeight()-_capsule1.getRadius();
  float height12 = _capsule2.getBase().z+_capsule2.getRadius();
  float height22 = _capsule2.getBase().z+_capsule2.getHeight()-_capsule1.getRadius();
  if((_capsule1.getBase().xy-_capsule2.getBase().xy).magnitud()
     < _capsule1.getRadius()+_capsule2.getRadius()
     && height11<height22 && height21 > height12)
  {
    return true;
  }
  Sphere s11(Vector3f(_capsule1.getBase().xy,
            _capsule1.getBase().z+_capsule1.getRadius()),_capsule1.getRadius());
  Sphere s21(Vector3f(_capsule1.getBase().xy,
            _capsule1.getBase().z+_capsule1.getHeight()-_capsule1.getRadius()),_capsule1.getRadius());
  Sphere s12(Vector3f(_capsule2.getBase().xy,
             _capsule2.getBase().z+_capsule2.getRadius()),_capsule2.getRadius());
  Sphere s22(Vector3f(_capsule2.getBase().xy,
             _capsule2.getBase().z+_capsule2.getHeight()-_capsule2.getRadius()),_capsule2.getRadius());

  return overlap(s11,s22) || overlap(s12,s21);
}

float 
PlatformMath::distance(const Line& _line, const Vector3f& _point)
{
  Vector3f u = _point - _line.getStaringPoint();
  return Vector3f::cross(_line.getDirection(),u).magnitud();
}

//float 
//PlatformMath::distance(const Line& _line1, const Line& _line2)
//{
//  auto dif = _line2.getStaringPoint() - _line1..getStaringPoint();
//  float v12 = Vector3f::dot(_line1.direction,_line1.direction);
//  float v22 = Vector3f::dot(_line2.direction,_line2.direction);
//  float v1v2 = Vector3f::dot(_line1.direction,_line2.direction);
//  float det = v1v2 * v1v2 - v12 * v22;
//  if (Math::abs(det) > FLT_MIN) {
//    det = 1.f / det;
//    float dpvl = Vector3f::dot(dif,_line1.direction);
//    float dpv2 = Vector3f::dot(dif,_line2.direction);
//    float t1 = (v1v2 * dpv2 - v22 * dpvl)* det;
//    float t2 = (v12 * dpv2 - v1v2 * dpvl) * det;
//    return (dif + _line2.direction * t2 - _line1.direction * t1).magnitud();
//  }
//  Vector3f a = Vector3f::cross(dif,_line1.direction);
//  return (sqrt( Vector3f::dot(a,a) / v12));
//}

float 
PlatformMath::distance(const Plane& _plane, const Vector3f& _point)
{
  return Vector3f::dot(_plane.getNormal(),_point)+_plane.getD();
}

bool 
PlatformMath::intersect(const Plane& _plane, const Line& _line, Vector3f& _point)
{
  auto direction = _line.getDirection();
  float fv = Vector3f::dot(_plane.getNormal(),direction);
  if (Math::abs(fv) > FLT_MIN) {
    _point = _line.getStaringPoint() 
           - direction
           * ((Vector3f::dot(_plane.getNormal(),_line.getStaringPoint())+_plane.getD()) / fv);
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
  Vector3f n =  Vector3f::cross(_plane1.getNormal(),_plane2.getNormal());
  float det = Vector3f::dot(n,_plane3.getNormal());
  if (abs(det) > FLT_MIN) {
    _point = (Vector3f::cross(_plane3.getNormal(),_plane2.getNormal()) * _plane1.getD() 
            + Vector3f::cross(_plane1.getNormal(),_plane3.getNormal()) * _plane2.getD() 
            - n * _plane3.getD()) / det;
    return true;
  }
  return false;
}

bool 
PlatformMath::intersect(const Plane& _plane1, const Plane& _plane2, Line& _line)
{
  //Vector3f dir = Vector3f::cross(_plane1.getNormal(),_plane2.getNormal());
  //_line.setDirection(dir);
  //float det = Vector3f::dot(dir,dir);
  //if (det > FLT_MIN) {
  //  _line.setStaringPoint((Vector3f::cross(dir,_plane1.getNormal()) * _plane2.getD() + Vector3f::cross(dir,_plane2.getNormal()) * _plane1.getD()) / det);
  //  return true;
  //}
  return false;
}

}
