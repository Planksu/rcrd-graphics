#include "vector_t.h"
#include <iostream>

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


	return 0;
}