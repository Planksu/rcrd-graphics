#ifndef _VECTOR_T_H_
#define _VECTOR_T_H_

#include <algorithm>
#include <type_traits>

namespace math
{
	template<typename... Ts> struct make_void { typedef void type; };
	template<typename... Ts> using void_t = typename make_void<Ts...>::type;

	template <unsigned int N, typename = void>
	class vector_t
	{
	public:
		vector_t() {};
		~vector_t() {};

	public:
		double data[N]; // Components

		// Typedefs
		typedef math::vector_t<2> Vector2;
		typedef math::vector_t<3> Vector3;
		typedef math::vector_t<4> Vector4;


	public:

		void normalize();
		float magnitude();
		vector_t<N> cross(const vector_t<N> &first, const vector_t<N> &other);

		// Overloaded operators
		vector_t<N>& operator=(vector_t<N> other)
		{
			std::swap(this->data, &other->x);
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
			return data[i];
		}

	};



	template <unsigned int N> class vector_t<2, void_t<typename std::enable_if<std::is_integral<N>::value>::type>
	{
		union
		{
			double data[2];
			struct { public: double x, y; };
		};
	};

	template <> class vector_t<3>
	{
		union
		{
			double data[3];
			struct { double x, y, z; };
		};
	};

	template <> class vector_t<4>
	{
		union
		{
			double data[4];
			struct { public: double x, y, z, w; };
		};

	};


}



#endif
