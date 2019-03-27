#include "vector_t.h"
#include "matrix_4.h"
#include <iostream>
#include <vector>

void printvec(const char* name, const math::vector_t<3> v)
{
	printf("%-12s = <%2.2f, %2.2f, %2.2f>\n", name, v.data[0], v.data[1], v.data[2]);
}

void printvec(const char* name, const math::vector_t<4> v)
{
	printf("%-12s = <%2.2f, %2.2f, %2.2f, %2.2f>\n", name, v.data[0], v.data[1], v.data[2], v.data[3]);
}

int main(int argc, char** argv)
{
	math::vector_t<3> first;
	math::vector_t<3> second;


	// Fill with some values
	for (size_t i = 0; i < 3; i++)
	{
		first.data[i] = (i+1)*2;
		second.data[i] = (i+3)*5;
	}

	printvec("first", first);
	printvec("second", second);

	printf("first length: %f\n", first.magnitude<3>());

	printvec("first + second", first + second);
	printvec("first - second", first - second);

	printvec("first cross second", first.cross(second));

	math::matrix_4 identity		= math::matrix_4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	math::matrix_4 transpose	= math::matrix_4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	math::matrix_4 inverse		= math::matrix_4(5, -2, 2, 7, 1, 0, 0, 3, -3, 1, 5, 0, 3, -1, -9, 4);
	math::vector_t<4> third;

	for (size_t i = 0; i < 4; i++)
	{
		third.data[i] = (i + 1) * 3;
	}

	printf("%f\n", inverse.determinant());

	transpose.transpose();
	inverse.inverse();

	math::vector_t<4> result = inverse * third;
	printvec("identity matrix * vec4", result);


	return 0;
}