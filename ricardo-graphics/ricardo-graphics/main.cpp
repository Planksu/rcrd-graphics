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
	math::matrix_4 identity = math::matrix_4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	math::matrix_4 rotMatX = math::matrix_4::rotationX(45 * (3.14f / 180));
	math::matrix_4 rotMatY = math::matrix_4::rotationY(180 * (3.14f / 180));
	math::matrix_4 rotMatZ = math::matrix_4::rotationZ(90 * (3.14f / 180));
	math::vector_t<4> first;
	math::vector_t<4> second;
	math::vector_t<4> third;
	math::vector_t<4> fourth;

	first.data[0] = 1; first.data[1] = 2; first.data[2] = 3; first.data[3] = 4;
	second.data[0] = 1; second.data[1] = 0; second.data[2] = 0; second.data[3] = 0;
	third.data[0] = 0; third.data[1] = 1; third.data[2] = 0; third.data[3] = 0;
	fourth.data[0] = -1; fourth.data[1] = -1; fourth.data[2] = -1; fourth.data[3] = 0;
	
	math::vector_t<4> res1 = identity * first;
	math::vector_t<4> res2 = rotMatX * second;
	math::vector_t<4> res3 = rotMatY * second;
	math::vector_t<4> res4 = rotMatZ * third;
	math::vector_t<4> res5 = rotMatX.inverse() * third;
	math::vector_t<4> res6 = rotMatZ * rotMatY * rotMatX.inverse() * fourth;

	printvec("res1", res1);
	printvec("res2", res2);
	printvec("res3", res3);
	printvec("res4", res4);
	printvec("res5", res5);
	printvec("res6", res6);


	//math::vector_t<3> first;
	//math::vector_t<3> second;

	//// Fill with some values
	//for (size_t i = 0; i < 3; i++)
	//{
	//	first.data[i] = (i+1)*2;
	//	second.data[i] = (i+3)*5;
	//}

	//printvec("first", first);
	//printvec("second", second);

	//printf("first length: %f\n", first.magnitude<3>());

	//printvec("first + second", first + second);
	//printvec("first - second", first - second);

	//printvec("first cross second", first.cross(second));

	return 0;
}