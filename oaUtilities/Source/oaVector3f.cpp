#include "..\Include\oaVector3f.h"
namespace oaEngineSDK {
Vector3f::Vector3f(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}
float& 
Vector3f::operator[](uint8 i) {
	return ((&x)[i]);
}
Vector3f 
Vector3f::operator+(Vector3f& v)
{
	return { x + v.x , y + v.y, z + v.z };
}
void 
Vector3f::operator+=(Vector3f& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}
Vector3f 
Vector3f::operator-(Vector3f& v)
{
	return { x - v.x , y - v.y, z - v.z };
}

void 
Vector3f::operator-=(Vector3f& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

Vector3f 
Vector3f::operator*(float v)
{
	return { x * v , y * v , z * v };
}

void 
Vector3f::operator*=(float v)
{
	x *= v;
	y *= v;
	z *= v;
}

Vector3f 
Vector3f::operator/(float v)
{
	v = 1.f / v;
	return { x * v , y * v, z * v };
}

void 
Vector3f::operator/=(float v)
{
	v = 1.f / v;
	x *= v;
	y *= v;
	z *= v;
}

float 
Vector3f::dot(Vector3f& v)
{
	return x * v.x + y * v.y + z * v.z;
}

float 
Vector3f::len()
{
	return Sqrt(x * x + y * y + z * z);
}

Vector3f 
Vector3f::normal()
{
	return *this * InvSqrt(x * x + y * y + z * z);
}

Vector3f 
Vector3f::cross(Vector3f& v)
{
	return Vector3f(y*v.z-z*v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

Vector3f 
Vector3f::project(Vector3f& v)
{
	return v * (dot(v) / v.dot(v));
}


bool 
operator==(Vector3f v1, Vector3f v2)
{
	return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

}


