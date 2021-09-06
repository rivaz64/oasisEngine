#pragma once
#include"oaPrerequisitesUtilities.h"

namespace oaEngineSDK {
/**
 * @brief bidimencional vector of floats
*/
class OA_UTILITY_EXPORT Vector2f
{
 public:
	float x;
	float y;
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
	inline float dot(Vector2f& v);
	/**
	 * @brief the lenght of the vector
	 * @return 
	*/
	inline float len();
	/**
	 * @brief the unitary form of the vector
	 * @return 
	*/
	inline Vector2f normal();
	/**
	 * @brief proyects this vector into v
	 * @param v 
	 * @return 
	*/
	inline Vector2f project(Vector2f& v);
};
bool OA_UTILITY_EXPORT operator==(Vector2f v1, Vector2f v2);
}