#include "..\Include\oaMatrix4f.h"
namespace oaEngineSDK {
Matrix4f::Matrix4f(Vector4f _a, Vector4f _b, Vector4f _c, Vector4f _d)
{
	a = _a;
	b = _b;
	c = _c;
	d = _d;
}

Matrix4f::Matrix4f(float f)
{
	a = { f,0.f,0.f,0.f };
	b = { 0.f,f,0.f,0.f };
	c = { 0.f,0.f,f,0.f };
	d = { 0.f,0.f,0.f,f };
}

Vector4f& Matrix4f::operator[](uint8 i)
{
	return ((&a)[i]);
}

Matrix4f oaEngineSDK::Matrix4f::operator+(Matrix4f& m)
{
	return { m.a + a,m.b + b,m.c + c,m.d + d };
}

void oaEngineSDK::Matrix4f::operator+=(Matrix4f& m)
{
	a += m.a;
	b += m.b;
	c += m.c;
	d += m.d;
}
Matrix4f Matrix4f::operator-(Matrix4f& m)
{
	return { a - m.a,b - m.b,c - m.c,d - m.d };
}
void Matrix4f::operator-=(Matrix4f& m)
{
	a -= m.a;
	b -= m.b;
	c -= m.c;
	d -= m.d;
}
Matrix4f Matrix4f::operator*(float m)
{
	return { a * m,b * m,c * m,d * m };
}
void Matrix4f::operator*=(float m)
{
	a *= m;
	b *= m;
	c *= m;
	d *= m;
}
Vector4f Matrix4f::operator*(Vector4f& v)
{
	return { a.dot(v),b.dot(v),c.dot(v),d.dot(v) };
}
Matrix4f Matrix4f::operator*(Matrix4f& m)
{
	return { {
			a.x * m.a.x + a.y * m.b.x + a.z * m.c.x + a.w * m.d.x,
			a.x * m.a.y + a.y * m.b.y + a.z * m.c.y + a.w * m.d.y,
			a.x * m.a.z + a.y * m.b.z + a.z * m.c.z + a.w * m.d.z,
			a.x * m.a.w + a.y * m.b.w + a.z * m.c.w + a.w * m.d.w
			},{
			b.x * m.a.x + b.y * m.b.x + b.z * m.c.x + b.w * m.d.x,
			b.x * m.a.y + b.y * m.b.y + b.z * m.c.y + b.w * m.d.y,
			b.x * m.a.z + b.y * m.b.z + b.z * m.c.z + b.w * m.d.z,
			b.x * m.a.w + b.y * m.b.w + b.z * m.c.w + b.w * m.d.w
			},{
			c.x * m.a.x + c.y * m.b.x + c.z * m.c.x + c.w * m.d.x,
			c.x * m.a.y + c.y * m.b.y + c.z * m.c.y + c.w * m.d.y,
			c.x * m.a.z + c.y * m.b.z + c.z * m.c.z + c.w * m.d.z,
			c.x * m.a.w + c.y * m.b.w + c.z * m.c.w + c.w * m.d.w 
			},{
			d.x * m.a.x + d.y * m.b.x + d.z * m.c.x + d.w * m.d.x,
			d.x * m.a.y + d.y * m.b.y + d.z * m.c.y + d.w * m.d.y,
			d.x * m.a.z + d.y * m.b.z + d.z * m.c.z + d.w * m.d.z,
			d.x * m.a.w + d.y * m.b.w +	d.z * m.c.w + d.w * m.d.w
			} };
}
void Matrix4f::operator*=(Matrix4f& m)
{
	a = {
			a.x* m.a.x + a.y * m.b.x + a.z * m.c.x + a.w * m.d.x,
			a.x* m.a.y + a.y * m.b.y + a.z * m.c.y + a.w * m.d.y,
			a.x* m.a.z + a.y * m.b.z + a.z * m.c.z + a.w * m.d.z,
			a.x* m.a.w + a.y * m.b.w + a.z * m.c.w + a.w * m.d.w
	};
	b = {
			b.x* m.a.x + b.y * m.b.x + b.z * m.c.x + b.w * m.d.x,
			b.x* m.a.y + b.y * m.b.y + b.z * m.c.y + b.w * m.d.y,
			b.x* m.a.z + b.y * m.b.z + b.z * m.c.z + b.w * m.d.z,
			b.x* m.a.w + b.y * m.b.w + b.z * m.c.w + b.w * m.d.w
	};
	c = {
			c.x* m.a.x + c.y * m.b.x + c.z * m.c.x + c.w * m.d.x,
			c.x* m.a.y + c.y * m.b.y + c.z * m.c.y + c.w * m.d.y,
			c.x* m.a.z + c.y * m.b.z + c.z * m.c.z + c.w * m.d.z,
			c.x* m.a.w + c.y * m.b.w + c.z * m.c.w + c.w * m.d.w
	};
	d = {
			d.x* m.a.x + d.y * m.b.x + d.z * m.c.x + d.w * m.d.x,
			d.x* m.a.y + d.y * m.b.y + d.z * m.c.y + d.w * m.d.y,
			d.x* m.a.z + d.y * m.b.z + d.z * m.c.z + d.w * m.d.z,
			d.x* m.a.w + d.y * m.b.w + d.z * m.c.w + d.w * m.d.w
	};
}
void Matrix4f::transpose()
{
	std::swap(a.y, b.x);
	std::swap(a.z, c.x);
	std::swap(b.z, c.y);
	std::swap(a.w, d.x);
	std::swap(b.w, d.y);
	std::swap(c.w, d.z);
}
bool OA_UTILITY_EXPORT operator==(Matrix4f m1, Matrix4f m2)
{
	return m1.a == m2.a && m1.b == m2.b && m1.c == m2.c;
}
}
