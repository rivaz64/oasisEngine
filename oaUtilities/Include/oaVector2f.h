#pragma once
#include"oaPrerequisitesUtilities.h"

namespace oaEngineSDK {
/**
 * @brief vector vidimensional de flotantes
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
	 * @brief el producto punto de dos vectores
	 * @param v 
	 * @return 
	*/
	float dot(Vector2f& v);
	/**
	 * @brief calcula la longitud del vector
	 * @return 
	*/
	float len();
	/**
	 * @brief te regresa el vector en su forma unitaria
	 * @return 
	*/
	Vector2f normal();
};
bool OA_UTILITY_EXPORT operator==(Vector2f v1, Vector2f v2);
}