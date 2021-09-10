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
	float& 
	operator[](uint8 i);
	/**
	 * @brief adds the vector v and this one
	 * @param v 
	 * @return 
	*/
	Vector2f 
	operator+(Vector2f& v);
	/**
	 * @brief adds the vector v to this one
	 * @param v 
	*/
	void 
	operator+=(Vector2f& v);
	/**
	 * @brief this vector minus vector v
	 * @param v 
	 * @return 
	*/
	Vector2f 
	operator-(Vector2f& v);
	/**
	 * @brief substract vector v from this
	 * @param v 
	*/
	void 
	operator-=(Vector2f& v);
	/**
	 * @brief calculates a vector with the same direction as this and a lenght multiplied by v
	 * @param v 
	 * @return 
	*/
	Vector2f
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
	Vector2f
	operator/(float v);
	/**
	 * @brief divide the length vector the vector by v
	 * @param v
	*/
	void 
	operator/=(float v);
	/**
	 * @brief dot product of to vector
	 * @param v 
	 * @return 
	*/
	float 
	dot(Vector2f& v);
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
	Vector2f 
	normal();
	/**
	 * @brief proyects this vector into v
	 * @param v 
	 * @return 
	*/
	Vector2f 
	project(Vector2f& v);
	/**
	 * @brief the direction in radians of the vector
	 * @return 
	*/
	float 
	getDirection();
	/**
	 * @brief changes the direction of the vector to r in radians and the lenght stays the same
	 * @return
	*/
	void
	setDirection(float r);
};
bool OA_UTILITY_EXPORT 
operator==(Vector2f v1, Vector2f v2);
}