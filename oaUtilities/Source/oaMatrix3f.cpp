#include "..\Include\oaMatrix3f.h"
namespace oaEngineSDK {
Matrix3f::Matrix3f(Vector3f _a, Vector3f _b, Vector3f _c)
{
	a = _a;
	b = _b;
	c = _c;
}

Matrix3f::Matrix3f(float f)
{
	a = { f,0.f,0.f };
	b = { 0.f,f,0.f };
	c = { 0.f,0.f,f };
}

Vector3f& Matrix3f::operator[](uint8 i)
{
	return ((&a)[i]);
}

Matrix3f oaEngineSDK::Matrix3f::operator+(Matrix3f& m)
{
	return { m.a + a,m.b + b,m.c + c };
}

void oaEngineSDK::Matrix3f::operator+=(Matrix3f& m)
{
	a += m.a;
	b += m.b;
	c += m.c;
}
Matrix3f Matrix3f::operator-(Matrix3f& m)
{
	return {a - m.a,b - m.b,c - m.c };
}
void Matrix3f::operator-=(Matrix3f& m)
{
	a -= m.a;
	b -= m.b;
	c -= m.c;
}
Matrix3f Matrix3f::operator*(float m)
{
	return { a * m,b * m,c * m };
}
void Matrix3f::operator*=(float m)
{
	a *= m;
	b *= m;
	c *= m;
}
Vector3f Matrix3f::operator*(Vector3f& v)
{
	return { a.dot(v),b.dot(v),c.dot(v) };
}
Matrix3f Matrix3f::operator*(Matrix3f& m)
{
	return { {
			a.x * m.a.x + a.y * m.b.x + a.z * m.c.x,
			a.x * m.a.y + a.y * m.b.y + a.z * m.c.y,
			a.x * m.a.z + a.y * m.b.z + a.z * m.c.z
			},{
			b.x * m.a.x + b.y * m.b.x + b.z * m.c.x,
			b.x * m.a.y + b.y * m.b.y + b.z * m.c.y,
			b.x * m.a.z + b.y * m.b.z + b.z * m.c.z
			},{
			c.x * m.a.x + c.y * m.b.x + c.z * m.c.x,
			c.x * m.a.y + c.y * m.b.y + c.z * m.c.y,
			c.x * m.a.z + c.y * m.b.z + c.z * m.c.z
			} };
}
void Matrix3f::operator*=(Matrix3f& m)
{
	a = {
		a.x * m.a.x + a.y * m.b.x + a.z * m.c.x,
			a.x * m.a.y + a.y * m.b.y + a.z * m.c.y,
			a.x * m.a.z + a.y * m.b.z + a.z * m.c.z
	};
	b = {
	b.x * m.a.x + b.y * m.b.x + b.z * m.c.x,
	b.x * m.a.y + b.y * m.b.y + b.z * m.c.y,
	b.x * m.a.z + b.y * m.b.z + b.z * m.c.z
	};
	c = {
	c.x * m.a.x + c.y * m.b.x + c.z * m.c.x,
	c.x * m.a.y + c.y * m.b.y + c.z * m.c.y,
	c.x * m.a.z + c.y * m.b.z + c.z * m.c.z
	};
}
void Matrix3f::transpose()
{
	std::swap(a.y,b.x);
	std::swap(a.z, c.x);
	std::swap(b.z, c.y);
}
float Matrix3f::determinant()
{
	return a.x*b.y*c.z+a.y*b.z*c.x+a.z*b.x*c.y
		-a.z*b.y*c.x-a.y*b.x*c.z-a.x*b.z*c.y;
}
bool OA_UTILITY_EXPORT operator==(Matrix3f m1, Matrix3f m2)
{
	return m1.a == m2.a && m1.b == m2.b && m1.c == m2.c;
}
}

