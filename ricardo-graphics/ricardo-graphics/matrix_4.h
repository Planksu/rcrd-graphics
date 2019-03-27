#ifndef _MATRIX_4_H
#define _MATRIX_4_H

#include <algorithm>
#include "vector_t.h"

namespace math
{
	class matrix_4
	{
	public:
		matrix_4(	double x1y1,
					double x2y1,
					double x3y1,
					double x4y1,
					double x1y2,
					double x2y2,
					double x3y2,
					double x4y2,
					double x1y3,
					double x2y3,
					double x3y3,
					double x4y3,
					double x1y4,
					double x2y4,
					double x3y4,
					double x4y4);

		matrix_4();

		~matrix_4() {};

	public:
		double data[4][4];


	public:
		void inverse();
		void transpose();
		double determinant();

		vector_t<4> operator*(const vector_t<4> &other)
		{
			vector_t<4> result;

			for (size_t i = 0; i < 4; i++)
			{
				double cell = 0;
				for (size_t j = 0; j < 4; j++)
				{
					cell += (data[i][j] * other.data[j]);
				}
				result.data[i] = cell;
			}

			return result;
		}
		

		static matrix_4 scale(double s);
		static matrix_4 translation(const vector_t<3> &t);
		static matrix_4 rotationX(double a);
		static matrix_4 rotationY(double a);
		static matrix_4 rotationZ(double a);

	private:

		void cofactor(double A[4][4], double temp[4][4], int rowToLeaveOut, int columnToLeaveOut, int n);
		void adjoint(double A[4][4], double adj[4][4], int n);
		double determinant(double A[4][4], int n);

	};

}

#endif