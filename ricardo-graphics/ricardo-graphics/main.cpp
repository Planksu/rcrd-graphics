#include "vector_t.h"
#include "matrix_txt.h"
#include <iostream>
#include <vector>

void printvec(const char* name, const math::vector_t<3> v)
{
	printf("%-12s = <%2.2f, %2.2f, %2.2f>\n", name, v.data[0], v.data[1], v.data[2]);
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

	math::matrix_txt<4> m;
	math::matrix_txt<4> m_transpose;
	std::vector<float> digits;

	for (size_t i = 0; i < 16; i++)
	{
		digits.push_back(pow(i, 2));
	}
	//m.Init(digits[0], digits[1], digits[2], digits[3], digits[4], digits[5], digits[6], digits[7], digits[8], digits[9], digits[10], digits[11], digits[12], digits[13], digits[14], digits[15]);
	m.Init(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	m_transpose.Init(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	m_transpose.transpose();

	printf("%f", m.det());


	return 0;
}