#include "vector_t.h"
#include <iostream>

int main(int argc, char** argv)
{
	vector_t<3> first;
	
	first.x = 3;

	while (1)
	{
		printf("%d", first.x);
	}

	return 0;
}