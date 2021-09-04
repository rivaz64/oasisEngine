#pragma once
#include"oaVector.h"
namespace oaEngineSDK {

template<class MatTyp, class T, int N, int S >
struct IDEN {
	enum {
		COL = N % S,
		ROW = N / S
	};
	static inline void id(MatTyp& m, T& value) {
		m[ROW][COL] = (COL == ROW) ? value : 0;
		IDEN< MatTyp,T, N - 1, S>::id(m,value);
	}
};
template<class MatTyp, class T, int S>
struct IDEN<MatTyp, T, 0, S> {
	static inline void id(MatTyp& m, T& value) {
		m[0][0] = value;
	}
};

/**
 * @brief template for square matrizes
 * @tparam T numeric type that the matrix is going to use
 * @tparam N the size of the matrix is N x N
*/
template<uint8 N, class T>
class Matrix {
	
};
template<class T>
class Matrix<2, T> {
public:
	MVector<2, T> a;
	MVector<2, T> b;
	MVector<2, T>& operator[](uint8 i) {
		return ((&a)[i]);
	}
};

template<class T>
class Matrix<3,T> {
public:
	MVector<3, T> a;
	MVector<3, T> b;
	MVector<3, T> c;
	MVector<3, T>& operator[](uint8 i) {
		return ((&a)[i]);
	}
	Matrix<3, T>() = default;
	Matrix<3, T>(T f) {
		IDEN< Matrix<3, float>, float, 8, 3>::id(*this, f);
	}
};
template<class T>
class Matrix<4, T> {
public:
	MVector<4, T> a;
	MVector<4, T> b;
	MVector<4, T> c;
	MVector<4, T> d;
	MVector<4, T>& operator[](uint8 i) {
		return ((&a)[i]);
	}
	Matrix<4, T>() = default;
	Matrix<4, T>(T f) {
		IDEN< Matrix<4, float>, float, 15, 4>::id(*this, f);
	}
};

class Matrix2f :
	public Matrix<2, float>
{
	float& operator[](uint8 i) {}
public:
	Matrix2f() = default;
	Matrix2f(Vector2f _a, Vector2f _b) {
		a = _a;
		b = _b;
	}
};

class Matrix3f :
	public Matrix<3, float>
{
	float& operator[](uint8 i) {}
public:
	Matrix3f() = default;
	Matrix3f(Vector3f _a, Vector3f _b, Vector3f _c) {
		a = _a;
		b = _b;
		c = _c;
	}
	/**
	 * @brief constructor for identity
	 * @param f the identity is going to be multiplied by this value
	*/
	Matrix3f(float f) :Matrix<3, float>(f) {}
};

class Matrix4f :
	public Matrix<4, float>
{
	float& operator[](uint8 i) {}
public:
	Matrix4f() = default;
	Matrix4f(Vector4f _a, Vector4f _b, Vector4f _c, Vector4f _d) {
		a = _a;
		b = _b;
		c = _c;
		d = _d;
	}
	/**
	 * @brief constructor for identity
	 * @param f the identity is going to be multiplied by this value
	*/
	Matrix4f(float f) :Matrix<4, float>(f) {}
};

template<uint8 N, class T>
bool operator==(Matrix<N, T> m1, Matrix<N, T> m2) {
	return EQVEC<Matrix<N, T>, N - 1>::com(m1, m2);
}
template<uint8 N, class T>
Matrix<N, T> operator+(Matrix<N, T> m1, Matrix<N, T> m2) {
	Matrix<N, T> ans;
	SUMVEC<Matrix<N, T>, N - 1>::sum(ans,m1, m2);
	return ans;
}

template<uint8 N, class T>
void operator+=(Matrix<N, T> m1, Matrix<N, T> m2) {
	SUVEC<Matrix<N, T>, N - 1>::sum(m1, m2);
}
}
