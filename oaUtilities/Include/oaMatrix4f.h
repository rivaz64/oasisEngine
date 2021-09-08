/**
 * @file oaVector2f.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */
#pragma once
#include"oaPrerequisitesUtilities.h"

namespace oaEngineSDK {

class Vector4f;

/**
 * @brief Matrix 3x3 of floats
*/
class OA_UTILITY_EXPORT Matrix4f
{
public:
	union {
		float data[16];
		Vector4f vectors[4];
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
	/**
	 * @brief calculates the determinant of the matrix
	 * @return
	*/
	float determinant();
private:
	/**
	 * @brief calculates the determinant of a minor matrix that is in the rows and colums
	 * @param r1 first row of the minor matrix
	 * @param r2 second row of the minor matrix
	 * @param r3 third row of the minor matrix
	 * @param c1 first column of the minor matrix
	 * @param c2 second column of the minor matrix
	 * @param c3 third column of the minor matrix
	 * @return
	*/
	float minorDet(uint8 r1, uint8 r2, uint8 r3, uint8 c1, uint8 c2, uint8 c3);
public:
	/**
	 * @brief calculates the inverse of a matrix, the inverse times this matrix is the identity matrix
	 * @return
	*/
	Matrix4f inverse();
};
bool OA_UTILITY_EXPORT operator==(Matrix4f m1, Matrix4f m2);
}