#pragma once
#include"oaPrerequisitesUtilities.h"
#include"oaVector3f.h"
namespace oaEngineSDK {

/**
 * @brief Matrix 3x3 of floats
*/
class OA_UTILITY_EXPORT Matrix3f
{
public:
	union {
		float data[9];
		struct {
			Vector3f a;
			Vector3f b;
			Vector3f c;
		};
	};
	Matrix3f() = default;
	Matrix3f(Vector3f _a, Vector3f _b, Vector3f _c);
	/**
	 * @brief constructor for an identity matrix
	 * @param f the idnetity matrix is going to be multiplied by f
	*/
	Matrix3f(float f);
	Vector3f& operator[](uint8 i);
	Matrix3f operator+(Matrix3f& m);
	void operator+=(Matrix3f& m);
	Matrix3f operator-(Matrix3f& m);
	void operator-=(Matrix3f& m);
	Matrix3f operator*(float m);
	void operator*=(float m);
	Vector3f operator*(Vector3f& v);
	Matrix3f operator*(Matrix3f& m);
	void operator*=(Matrix3f& m);
	/**
	 * @brief changes the rows for the columns
	*/
	void transpose();
};
bool OA_UTILITY_EXPORT operator==(Matrix3f m1, Matrix3f m2);
}


