/**
 * @file oaVector3f.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */

#pragma once
#include"oaPrerequisitesUtilities.h"

namespace oaEngineSDK {
/**
 * @brief tridimencional vector of floats
*/
class OA_UTILITY_EXPORT Vector3f
{
public:
	union {
		float data[3];
		struct {
			float x;
			float y;
			float z;
		};
	};
	
	Vector3f() = default;
	Vector3f(float _x, float _y, float _z);
	float& 
	operator[](uint8 i);
	/**
	 * @brief adds the vector v and this one
	 * @param v
	 * @return
	*/
	Vector3f 
	operator+(Vector3f& v);
	/**
	 * @brief adds the vector v to this one
	 * @param v
	*/
	void 
	operator+=(Vector3f& v);
	/**
	 * @brief this vector minus vector v
	 * @param v
	 * @return
	*/
	Vector3f 
	operator-(Vector3f& v);
	/**
	 * @brief substract vector v from this
	 * @param v
	*/
	void 
	operator-=(Vector3f& v);
	/**
	 * @brief calculates a vector with the same direction as this and a lenght multiplied by v
	 * @param v
	 * @return
	*/
	Vector3f 
	operator*(float v);
	/**
	 * @brief multiply the length vector the vector by v
	 * @param v
	*/
	void 
	operator*=(float v);
	/**
	 * @brief calculates a vector with the same direction as this and a lenght divided by v
	 * @param v
	 * @return
	*/
	Vector3f 
	operator/(float v);
	/**
	 * @brief divide the length vector the vector by v
	 * @param v
	*/
	void 
	operator/=(float v);
	/**
	 * @brief dot product of two vector
	 * @param v
	 * @return
	*/
	float 
	dot(Vector3f& v);
	/**
	 * @brief the lenght of the vector
	 * @return
	*/
	float 
	len();
	/**
	 * @brief the unitary form of the vector
	 * @return
	*/
	Vector3f 
	normal();
	/**
	 * @brief cross product of two vectors
	 * @param v 
	 * @return 
	*/
	Vector3f 
	cross(Vector3f& v);
	/**
	 * @brief proyects this vector into v
	 * @param v
	 * @return
	*/
	Vector3f 
	project(Vector3f& v);
};

const Vector3f rightVector = Vector3f(1, 0, 0);
const Vector3f leftVector = Vector3f(-1, 0, 0);
const Vector3f upVector = Vector3f(0, 1, 0);
const Vector3f downVector = Vector3f(0, -1, 0);
const Vector3f frontVector = Vector3f(0, 0, 1);
const Vector3f backVector = Vector3f(0, 0, -1);

bool OA_UTILITY_EXPORT 
operator==(Vector3f v1, Vector3f v2);
}
