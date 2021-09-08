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
	float& operator[](uint8 i);
	Vector3f operator+(Vector3f& v);
	void operator+=(Vector3f& v);
	Vector3f operator-(Vector3f& v);
	void operator-=(Vector3f& v);
	Vector3f operator*(float v);
	void operator*=(float v);
	Vector3f operator/(float v);
	void operator/=(float v);
	/**
	 * @brief dot product of two vector
	 * @param v
	 * @return
	*/
	float dot(Vector3f& v);
	/**
	 * @brief the lenght of the vector
	 * @return
	*/
	float len();
	/**
	 * @brief the unitary form of the vector
	 * @return
	*/
	Vector3f normal();
	/**
	 * @brief cross product of two vectors
	 * @param v 
	 * @return 
	*/
	Vector3f cross(Vector3f& v);
	/**
	 * @brief proyects this vector into v
	 * @param v
	 * @return
	*/
	Vector3f project(Vector3f& v);
};
bool OA_UTILITY_EXPORT operator==(Vector3f v1, Vector3f v2);
}
