#pragma once
#include"oaPrerequisitesUtilities.h"

namespace oaEngineSDK {
/**
 * @brief tetradimencional vector of floats
*/
class OA_UTILITY_EXPORT Vector4f
{
public:
	union {
		float data[3];
		struct {
			float x;
			float y;
			float z;
			float w;
		};
	};


	Vector4f() = default;
	Vector4f(float _x, float _y, float _z, float _w);
	float& operator[](uint8 i);
	Vector4f operator+(Vector4f& v);
	void operator+=(Vector4f& v);
	Vector4f operator-(Vector4f& v);
	void operator-=(Vector4f& v);
	Vector4f operator*(float v);
	void operator*=(float v);
	Vector4f operator/(float v);
	void operator/=(float v);
	/**
	 * @brief dot product of to vector
	 * @param v
	 * @return
	*/
	float dot(Vector4f& v);
	/**
	 * @brief the lenght of the vector
	 * @return
	*/
	float len();
	/**
	 * @brief the unitary form of the vector
	 * @return
	*/
	Vector4f normal();
	/**
	 * @brief proyects this vector into v
	 * @param v
	 * @return
	*/
	Vector4f project(Vector4f& v);
};
bool OA_UTILITY_EXPORT operator==(Vector4f v1, Vector4f v2);
}
