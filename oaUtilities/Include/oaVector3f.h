#pragma once
#include"oaPrerequisitesUtilities.h"

namespace oaEngineSDK {
/**
 * @brief tridimencional vector of floats
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
	 * @brief dot product of to vector
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
};
bool OA_UTILITY_EXPORT operator==(Vector3f v1, Vector3f v2);
}
