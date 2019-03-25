#include "vector_t.h"
#include <iostream>

int main(int argc, char** argv)
{
	math::vector_t<3> first;

	first.data[0] = 3;
	first.data[1] = 12;
	first.data[0] = 4;

	while (1)
	{
		printf("%f\n", first.data[1]);
	}

	return 0;
}