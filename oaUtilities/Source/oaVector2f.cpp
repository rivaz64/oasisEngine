#include "..\Include\oaVector2f.h"
namespace oaEngineSDK {
Vector2f::Vector2f(float _x, float _y)
{
	x = _x;
	y = _y;
}
float& Vector2f::operator[](uint8 i) {
	return ((&x)[i]);
}
Vector2f Vector2f::operator+(Vector2f& v)
{
	return { x + v.x , y + v.y };
}
void Vector2f::operator+=(Vector2f& v)
{
	x += v.x;
	y += v.y;
}
Vector2f Vector2f::operator-(Vector2f& v)
{
	return { x - v.x , y - v.y };
}

void Vector2f::operator-=(Vector2f& v)
{
	x -= v.x;
	y -= v.y;
}

Vector2f Vector2f::operator*(float v)
{
	return { x * v , y * v };
}

void Vector2f::operator*=(float v)
{
	x *= v;
	y *= v;
}

Vector2f Vector2f::operator/(float v)
{
	v = 1.f / v;
	return { x * v , y * v };
}

void Vector2f::operator/=(float v)
{
	v = 1.f / v;
	x *= v;
	y *= v;
}

float Vector2f::dot(Vector2f& v)
{
	return x*v.x+y*v.y;
}

float Vector2f::len()
{
	return Sqrt(x * x + y * y);
}

Vector2f Vector2f::normal()
{
	return *this*InvSqrt(x * x + y * y);
}


bool operator==(Vector2f v1, Vector2f v2)
{
	return v1.x == v2.x && v1.y == v2.y;
}

}

