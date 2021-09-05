#pragma once
#include"oaPrerequisitesUtilities.h"

namespace oaEngineSDK {
/**
 * @brief vector vidimensional de flotantes
*/
class OA_UTILITY_EXPORT Vector3f
{
public:
	float x;
	float y;
	float z;
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
	 * @brief el producto punto de dos vectores
	 * @param v
	 * @return
	*/
	float dot(Vector3f& v);
	/**
	 * @brief calcula la longitud del vector
	 * @return
	*/
	float len();
	/**
	 * @brief te regresa el vector en su forma unitaria
	 * @return
	*/
	Vector3f normal();
};
bool OA_UTILITY_EXPORT operator==(Vector3f v1, Vector3f v2);
}
