#pragma once
#include"oaPrerequisitesUtilities.h"
#include <type_traits>
namespace oaEngineSDK {

/**
 * @brief template class for a vector of n dimencions
 * @tparam D the dimencions of the vector
 * @tparam T the numerical type is going to use
*/
template<int N, class T>
class MVector {

};
template< class T>
class MVector<2, T>
{
public:
	T x;
	T y;
	MVector<2, T>() = default;
	MVector<2, T>(T _x, T _y) {
		x = _x;
		y = _y;
	}
	T& operator[](int i) {
		return ((&x)[i]);
	}
};
template< class T>
class MVector<3, T>
{
public:
	T x;
	T y;
	T z;
	MVector<3, T>() = default;
	MVector<3, T>(T _x, T _y, T _z) {
		x = _x;
		y = _y;
		z = _z;
	}
	T& operator[](int i) {
		return ((&x)[i]);
	}
};
template< class T>
class MVector<4, T>
{
public:
	T x;
	T y;
	T z;
	T w;
	MVector<4, T>() = default;
	MVector<4, T>(T _x, T _y, T _z, T _w) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
	T& operator[](int i) {
		return ((&x)[i]);
	}
};
typedef MVector<2, float> Vector2f;
typedef MVector<3, float> Vector3f;
typedef MVector<4, float> Vector4f;

template<class VecTyp, int N>
struct EQVEC {
	static inline bool com(VecTyp& v, VecTyp& o) {
		return v[N] == o[N] && EQVEC< VecTyp, N - 1>::com(v, o);
	}
};
template<class VecTyp>
struct EQVEC< VecTyp, 0> {
	static inline bool com(VecTyp& v, VecTyp& o) {
		return v[0] == o[0];
	}
};

template<int N, class T>
bool operator==(MVector<N, T>& v1, MVector<N, T>& v2) {
	return EQVEC<MVector<N, T>, N - 1>::com( v1, v2);
}

template<class VecTyp, int N>
struct DIFVEC {
	static inline bool com(VecTyp& v, VecTyp& o) {
		return v[N] != o[N] || DIFVEC< VecTyp, N - 1>::com(v, o);
	}
};
template<class VecTyp>
struct DIFVEC< VecTyp, 0> {
	static inline bool com(VecTyp& v, VecTyp& o) {
		return v[0] != o[0];
	}
};
template<int N, class T>
bool operator!=(MVector<N, T>& v1, MVector<N, T>& v2) {
	return DIFVEC<MVector<N, T>, N - 1>::com(v1, v2);
}


template<class VecTyp, int N>
struct SUMVEC {
	static inline void sum(VecTyp& a, VecTyp& v, VecTyp& o) {
		a[N] = v[N] + o[N];
		SUMVEC< VecTyp, N - 1>::sum(a, v, o);
	}
};
template<class VecTyp>
struct SUMVEC< VecTyp, 0> {
	static inline void sum(VecTyp& a, VecTyp& v, VecTyp& o) {
		a[0] = v[0] + o[0];
	}
};

template<int N, class T>
MVector<N, T> operator+(MVector<N, T>& v1, MVector<N, T>& v2) {
	MVector<N, T> ans;
	SUMVEC<MVector<N, T>, N - 1>::sum(ans, v1,v2);
	return ans;
}

template<class VecTyp, int N>
struct SUVEC {
	static inline void sum(VecTyp& v, VecTyp& o) {
		v[N] += o[N];
		SUVEC< VecTyp, N - 1>::sum(v, o);
	}
};
template<class VecTyp>
struct SUVEC< VecTyp, 0> {
	static inline void sum(VecTyp& v, VecTyp& o) {
		v[0] += o[0];
	}
};

template<int N, class T>
void operator+=(MVector<N, T>& v1, MVector<N, T>& v2) {
	SUVEC<MVector<N, T>, N - 1>::sum(v1, v2);
}




template<class VecTyp, int N>
struct RESVEC {
	static inline void res(VecTyp& a, VecTyp& v, VecTyp& o) {
		a[N] = v[N] - o[N];
		RESVEC< VecTyp, N - 1>::res(a, v, o);
	}
};
template<class VecTyp>
struct RESVEC< VecTyp, 0> {
	static inline void res(VecTyp& a, VecTyp& v, VecTyp& o) {
		a[0] = v[0] - o[0];
	}
};

template<int N, class T>
MVector<N, T> operator-(MVector<N, T>& v1, MVector<N, T>& v2) {
	MVector<N, T> ans;
	RESVEC<MVector<N, T>, N - 1>::res(ans, v1, v2);
	return ans;
}

template<class VecTyp, int N>
struct REVEC {
	static inline void res(VecTyp& v, VecTyp& o) {
		v[N] -= o[N];
		REVEC< VecTyp, N - 1>::res(v, o);
	}
};
template<class VecTyp>
struct REVEC< VecTyp, 0> {
	static inline void res(VecTyp& v, VecTyp& o) {
		v[0] -= o[0];
	}
};

template<int N, class T>
void operator-=(MVector<N, T>& v1, MVector<N, T>& v2) {
	REVEC<MVector<N, T>, N - 1>::res(v1, v2);
}



template<class VecTyp, int N, class T>
struct MULVEC {
	static inline void mul(VecTyp& a, VecTyp& v, T& o) {
		a[N] = v[N] * o;
		MULVEC< VecTyp, N - 1,T>::mul(a, v, o);
	}
};
template<class VecTyp, class T>
struct MULVEC< VecTyp, 0, T> {
	static inline void mul(VecTyp& a, VecTyp& v, T& o) {
		a[0] = v[0] * o;
	}
};

template<int N, class T>
MVector<N, T> operator*(MVector<N, T>& v1, T n) {
	MVector<N, T> ans;
	MULVEC<MVector<N, T>, N - 1,T>::mul(ans, v1, n);
	return ans;
}

template<class VecTyp, int N, class T>
struct MUVEC {
	static inline void mul(VecTyp& v, T& o) {
		v[N] *= o;
		MUVEC< VecTyp, N - 1,T>::mul(v, o);
	}
};
template<class VecTyp, class T>
struct MUVEC< VecTyp, 0,T> {
	static inline void mul(VecTyp& v, T& o) {
		v[0] *= o;
	}
};

template<int N, class T>
void operator*=(MVector<N, T>& v1, T v2) {
	MUVEC<MVector<N, T>, N - 1,T>::mul(v1, v2);
}



template<class VecTyp, int N, class T>
struct DOT {
	static inline T mul(VecTyp& v1, VecTyp& v2) {
		return v1[N]*v2[N] + DOT< VecTyp, N - 1, T>::mul(v1,v2);
	}
};
template<class VecTyp, class T>
struct DOT< VecTyp, 0, T> {
	static inline T mul(VecTyp& v1, VecTyp& v2) {
		return v1[0] * v2[0];
	}
};
template<int N, class T>
inline T operator*(MVector<N, T>& v1, MVector<N, T>& v2) {
	return DOT<MVector<N, T>, N - 1, T>::mul(v1, v2);
}


template<int N, class T>
inline T length(MVector<N, T>& v1) {
	return Sqrt(v1*v1);
}

template<int N, class T>
inline MVector<N, T> normalize(MVector<N, T>& v1) {
	return v1*InvSqrt(v1 * v1);
}

}
