/**
 * @file oaVector2f.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */

#pragma once
#include"oaPrerequisitesUtilities.h"



namespace oaEngineSDK {

class Vector2f;
class Vector3f;

/**
 * @brief Matrix 3x3 of floats
*/
class OA_UTILITY_EXPORT Matrix3f
{
public:
	union {
		float data[9];
		Vector3f vectors[3];
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
	/**
	 * @brief adds the matrix m and this one
	 * @param m
	 * @return
	*/
	Matrix3f operator+(Matrix3f& m);
	/**
	 * @brief adds the matrix m to this one
	 * @param m
	*/
	void operator+=(Matrix3f& m);
	/**
	 * @brief this matrix minus m
	 * @param m
	 * @return
	*/
	Matrix3f operator-(Matrix3f& m);
	/**
	 * @brief subtracts m from this matrix
	 * @param m
	*/
	void operator-=(Matrix3f& m);
	/**
	 * @brief the multiplication of this matrix times m
	 * @param m
	 * @return
	*/
	Matrix3f operator*(float m);
	/**
	 * @brief multiplies this matrix times m
	 * @param m
	*/
	void operator*=(float m);
	/**
	 * @brief the multiplication of this matrix and the vector v
	 * @param v
	 * @return
	*/
	Vector3f operator*(Vector3f& v);
	/**
	 * @brief the multiplication of this matrix and the matrix m
	 * @param v
	 * @return
	*/
	Matrix3f operator*(Matrix3f& m);
	/**
	 * @brief multiplies this matrix times the matrix m
	 * @param m 
	*/
	void operator*=(Matrix3f& m);
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
	 * @param c1 first column of the minor matrix
	 * @param c2 second column of the minor matrix
	 * @return 
	*/
	float minorDet(uint8 r1, uint8 r2, uint8 c1, uint8 c2);
public:
	/**
	 * @brief calculates the inverse of a matrix, the inverse times this matrix is the identity matrix
	 * @return 
	*/
	Matrix3f inverse();
	/**
	 * @brief creates a translate matrix for the given position
	*/
	static Matrix3f translateMatrix(Vector2f v);
	/**
	 * @brief creates a scale matrix for the given size
	*/
	static Matrix3f scaleMatrix(Vector2f v);
};
bool OA_UTILITY_EXPORT operator==(Matrix3f m1, Matrix3f m2);
}


