#include "vector_t.h"


template<unsigned int N> void vector_t<N>::normalize()
{
	float norm = 0.0f;

	// Calculate the sum of components power of two
	for (size_t i = 0; i < N; i++)
	{
		norm += x[i] * x[i];
	}

	// Apply the calculated norm to the vector components
	norm = 1.0f / sqrt(norm);
	for (size_t i = 0; i < N; i++)
	{
		x[i] *= norm;
	}
}

template<unsigned int N> float vector_t<N>::magnitude()
{
	float length = 0.0f;
	for (size_t i = 0; i < N; i++)
	{
		length += x[i];
	}

	// Calculate the square root here to do it only once, save cpu time
	return sqrt(length);
}

template<unsigned int N> vector_t<N> vector_t<N>::cross(const vector_t<N> &first, const vector_t<N> &other)
{
	if (N != 3)
	{
		printf("Cross product only for three dimensional vectors");
		return vector_t<N>;
	}

	vector_t<N> crossResult;

	crossResult[0] = (first.x[1] * other.x[2]) - (first.x[2] * other.x[1]);
	crossResult[1] = (first.x[2] * other.x[0]) - (first.x[0] * other.x[2]);
	crossResult[2] = (first.x[0] * other.x[1]) - (first.x[1] * other.x[0]);

	return crossResult;
}