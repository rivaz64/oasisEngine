#include "..\Include\oaVector4f.h"
namespace oaEngineSDK {
Vector4f::Vector4f(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}
float& 
Vector4f::operator[](uint8 i) {
	return ((&x)[i]);
}
Vector4f 
Vector4f::operator+(Vector4f& v)
{
	return { x + v.x , y + v.y, z + v.z, w + v.w };
}
void 
Vector4f::operator+=(Vector4f& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;

}
Vector4f 
Vector4f::operator-(Vector4f& v)
{
	return { x - v.x , y - v.y, z - v.z, w - v.w };
}

void 
Vector4f::operator-=(Vector4f& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
}

Vector4f 
Vector4f::operator*(float v)
{
	return { x * v , y * v , z * v, w * v };
}

void 
Vector4f::operator*=(float v)
{
	x *= v;
	y *= v;
	z *= v;
	w *= v;
}

Vector4f 
Vector4f::operator/(float v)
{
	v = 1.f / v;
	return { x * v , y * v, z * v , w * v };
}

void 
Vector4f::operator/=(float v)
{
	v = 1.f / v;
	x *= v;
	y *= v;
	z *= v;
	w *= v;
}

float 
Vector4f::dot(Vector4f& v)
{
	return x * v.x + y * v.y + z * v.z+ w * v.w;
}

float 
Vector4f::len()
{
	return Sqrt(x * x + y * y + z * z +w * w);
}

Vector4f 
Vector4f::normal()
{
	return *this * InvSqrt(x * x + y * y + z * z + w * w);
}

Vector4f 
Vector4f::project(Vector4f& v)
{
	return v * (dot(v) / v.dot(v));
}


bool 
operator==(Vector4f v1, Vector4f v2)
{
	return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
}

}


