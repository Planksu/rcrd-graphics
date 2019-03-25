#ifndef _VECTOR_T_H_
#define _VECTOR_T_H_

#include <algorithm>

namespace math
{
	template <unsigned int N>
	class vector_t
	{
	public:
		vector_t() {};
		~vector_t() {};

	public:
		// Components
		double data[N]; 

		// Typedefs
		typedef math::vector_t<2> Vector2;
		typedef math::vector_t<3> Vector3;
		typedef math::vector_t<4> Vector4;


	public:

		template<unsigned int N> void normalize()
		{
			float norm = 0.0f;

			// Calculate the sum of components power of two
			for (size_t i = 0; i < N; i++)
			{
				norm += data[i] * data[i];
			}

			// Apply the calculated norm to the vector components
			norm = 1.0f / sqrt(norm);
			for (size_t i = 0; i < N; i++)
			{
				data[i] *= norm;
			}
		}

		template<unsigned int N> float magnitude()
		{
			float length = 0.0f;
			for (size_t i = 0; i < N; i++)
			{
				length += pow(data[i],2);
			}

			// Calculate the square root here to do it only once, save cpu time
			return sqrt(length);
		}

		template<unsigned int N = 3> vector_t<N> cross(const vector_t<3> other)
		{
			vector_t<3> crossResult;

			crossResult.data[0] = (this->data[1] * other.data[2]) - (this->data[2] * other.data[1]);
			crossResult.data[1] = (this->data[2] * other.data[0]) - (this->data[0] * other.data[2]);
			crossResult.data[2] = (this->data[0] * other.data[1]) - (this->data[1] * other.data[0]);

			return crossResult;
		}

		template<unsigned int N = 2> float cross2x2(const vector_t<2> &other)
		{
			return this.data[0] * other.data[1] - this.data[1] * other.data[0];
		}

		template <unsigned int N>
		vector_t<N> operator+(const vector_t<N> &other)
		{
			vector_t<N> copy = *this;
			for (size_t i = 0; i < N; i++)
			{
				copy.data[i] = copy.data[i] + other.data[i];
			}
			return copy;
		}

		template <unsigned int N>
		vector_t<N> operator-(const vector_t<N> &other)
		{
			vector_t<N> copy = *this;
			for (size_t i = 0; i < N; i++)
			{
				copy.data[i] = copy.data[i] - other.data[i];
			}
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
			return data[i];
		}

	};

	// Specializations (dont work)

	//template <unsigned int N> class vector_t<2, void_t<typename std::enable_if<std::is_integral<N>::value>::type>
	//{
	//	union
	//	{
	//		double data[2];
	//		struct { public: double x, y; };
	//	};
	//};

	//template <> class vector_t<3>
	//{
	//	union
	//	{
	//		double data[3];
	//		struct { double x, y, z; };
	//	};
	//};

	//template <> class vector_t<4>
	//{
	//	union
	//	{
	//		double data[4];
	//		struct { public: double x, y, z, w; };
	//	};

	//};
}



#endif
