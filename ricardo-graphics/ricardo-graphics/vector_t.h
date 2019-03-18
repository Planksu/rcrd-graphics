#ifndef _VECTOR_T_H_
#define _VECTOR_T_H_

#include <algorithm>

template <unsigned int N>
class vector_t
{
public:
	vector_t() {};
	~vector_t() {};

public:
	double x[N]; // Components

public:

	void normalize();
	float magnitude();
	vector_t<N> cross(const vector_t<N> &first, const vector_t<N> &other);

	// Overloaded operators
	vector_t<N>& operator=(vector_t<N> other)
	{
		std::swap(this->x, &other->x);
		return *this;
	}

	template <unsigned int N>
	vector_t<N> operator+(const vector_t<N> &other)
	{
		const vector_t<N> copy = this;
		copy += other;
		return copy;
	}

	template <unsigned int N>
	vector_t<N> operator-(const vector_t<N> &other)
	{
		const vector_t<N> copy = this;
		copy -= other;
		return copy;
	}

	template <unsigned int N>
	vector_t<N> operator*(float &scalar)
	{
		const vector_t<N> copy = this;
		for (size_t i = 0; i < N; i++)
		{
			copy->x[i] *= scalar;
		}
		return copy;
	}

	template <unsigned int N>
	vector_t<N> operator[](size_t i)
	{
		return x[i];
	}

};

typedef vector_t<2> Vector2;
typedef vector_t<3> Vector3;
typedef vector_t<4> Vector4;

// Specializations
template <> class vector_t<2> { union { double x[2]; struct { float x, y; }; }; };
template <> class vector_t<3> { union { double x[3]; struct { float x, y, z; }; }; };
template <> class vector_t<4> { union { double x[4]; struct { float x, y, z, w; }; }; };


#endif
