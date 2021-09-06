#pragma once
#include"oaPrerequisitesUtilities.h"
#include"oaVector4f.h"
namespace oaEngineSDK {

/**
 * @brief Matrix 3x3 of floats
*/
class OA_UTILITY_EXPORT Matrix4f
{
public:
	union {
		float data[16];
		struct {
			Vector4f a;
			Vector4f b;
			Vector4f c;
			Vector4f d;
		};
	};
	Matrix4f() = default;
	Matrix4f(Vector4f _a, Vector4f _b, Vector4f _c, Vector4f _d);
	/**
	 * @brief constructor for an identity matrix
	 * @param f the idnetity matrix is going to be multiplied by f
	*/
	Matrix4f(float f);
	Vector4f& operator[](uint8 i);
	Matrix4f operator+(Matrix4f& m);
	void operator+=(Matrix4f& m);
	Matrix4f operator-(Matrix4f& m);
	void operator-=(Matrix4f& m);
	Matrix4f operator*(float m);
	void operator*=(float m);
	Vector4f operator*(Vector4f& v);
	Matrix4f operator*(Matrix4f& m);
	void operator*=(Matrix4f& m);
	/**
	 * @brief changes the rows for the columns
	*/
	void transpose();
};
bool OA_UTILITY_EXPORT operator==(Matrix4f m1, Matrix4f m2);
}