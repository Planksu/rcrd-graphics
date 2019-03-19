#include "vector_t.h"
#include <iostream>

int main(int argc, char** argv)
{
	math::vector_t<3> first;

	first.x = 3;
	first.y = 12;
	first.data[0] = 4;

	while (1)
	{
		printf("%d", first.y);
	}

	return 0;
}