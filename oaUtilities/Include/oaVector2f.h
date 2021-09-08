/**
 * @file oaVector2f.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */

#pragma once
#include"oaPrerequisitesUtilities.h"

namespace oaEngineSDK {
/**
 * @brief bidimencional vector of floats
*/
class OA_UTILITY_EXPORT Vector2f
{
 public:

	 union {
		 float data[2];
		 struct {
			 float x;
			 float y;
		 };
	 };
	
	Vector2f() = default;
	Vector2f(float _x, float _y);
	float& operator[](uint8 i);
	Vector2f operator+(Vector2f& v);
	void operator+=(Vector2f& v);
	Vector2f operator-(Vector2f& v);
	void operator-=(Vector2f& v);
	Vector2f operator*(float v);
	void operator*=(float v);
	Vector2f operator/(float v);
	void operator/=(float v);
	/**
	 * @brief dot product of to vector
	 * @param v 
	 * @return 
	*/
	float dot(Vector2f& v);
	/**
	 * @brief the lenght of the vector
	 * @return 
	*/
	float len();
	/**
	 * @brief the unitary form of the vector
	 * @return 
	*/
	Vector2f normal();
	/**
	 * @brief proyects this vector into v
	 * @param v 
	 * @return 
	*/
	Vector2f project(Vector2f& v);
};
bool OA_UTILITY_EXPORT operator==(Vector2f v1, Vector2f v2);
}