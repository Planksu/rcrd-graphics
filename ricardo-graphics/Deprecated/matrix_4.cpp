#include "matrix_4.h"

namespace math
{
	matrix_4::matrix_4(	double x1y1,
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
						double x4y4)
	{
		double data1[4] = { x1y1, x2y1, x3y1, x4y1 };
		double data2[4] = { x1y2, x2y2, x3y2, x4y2 };
		double data3[4] = { x1y3, x2y3, x3y3, x4y3 };
		double data4[4] = { x1y4, x2y4, x3y4, x4y4 };

		std::copy(data1, data1 + 4, data[0]);
		std::copy(data2, data2 + 4, data[1]);
		std::copy(data3, data3 + 4, data[2]);
		std::copy(data4, data4 + 4, data[3]);
	}

	matrix_4::matrix_4()
	{
		double data1[4] = { 0,0,0,0 };
		double data2[4] = { 0,0,0,0 };
		double data3[4] = { 0,0,0,0 };
		double data4[4] = { 0,0,0,0 };

		std::copy(data1, data1 + 4, data[0]);
		std::copy(data2, data2 + 4, data[1]);
		std::copy(data3, data3 + 4, data[2]);
		std::copy(data4, data4 + 4, data[3]);
	}

	matrix_4 matrix_4::scale(double s)
	{
		return matrix_4(s, 0, 0, 0, 0, s, 0, 0, 0, 0, s, 0, 0, 0, 0, s);
	}

	matrix_4 matrix_4::translation(const vector_t<3> &t)
	{
		return matrix_4(1, 0, 0, t.data[0], 0, 1, 0, t.data[1], 0, 0, 1, t.data[2], 0, 0, 0, 1);
	}

	matrix_4 matrix_4::rotationX(double a)
	{
		return matrix_4(1, 0, 0, 0, 0, cos(a), -sin(a), 0, 0, sin(a), cos(a), 0, 0, 0, 0, 1);
	}

	matrix_4 matrix_4::rotationY(double a)
	{
		return matrix_4(cos(a), 0, sin(a), 0, 0, 1, 0, 0, -sin(a), 0, cos(a), 0, 0, 0, 0, 1);
	}

	matrix_4 matrix_4::rotationZ(double a)
	{
		return matrix_4(cos(a), -sin(a), 0, 0, sin(a), cos(a), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	}

	void matrix_4::transpose()
	{
		double dataT[4][4];

		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				dataT[j][i] = data[i][j];
			}
		}

		for (size_t i = 0; i < 4; i++)
		{
			std::copy(dataT[i], dataT[i] + 4, data[i]);
		}
	}

	void matrix_4::cofactor(double A[4][4], double temp[4][4], int rowToLeaveOut, int columnToLeaveOut, int n)
	{
		int i = 0;
		int j = 0;

		for (size_t row = 0; row < n; row++)
		{
			for (size_t column = 0; column < n; column++)
			{
				if (row != rowToLeaveOut && column != columnToLeaveOut)
				{
					temp[i][j++] = A[row][column];

					if (j == n - 1)
					{
						j = 0;
						i++;
					}
				}
			}
		}
	}

	double matrix_4::determinant(double A[4][4], int n)
	{
		double det = 0;

		if (n == 1)
			return A[0][0];

		double temp[4][4];
		int sign = 1;

		for (size_t i = 0; i < n; i++)
		{
			cofactor(A, temp, 0, i, n);
			det += sign * A[0][i] * determinant(temp, n - 1);

			sign = -sign;
		}

		return det;
	}

	double matrix_4::determinant()
	{
		// Transform our matrix into double[4][4] form
		double contents[4][4];

		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				contents[i][j] = data[i][j];
			}
		}

		return determinant(contents, 4);
	}

	void matrix_4::adjoint(double A[4][4], double adj[4][4], int n)
	{
		if (n == 1)
		{
			adj[0][0] = 1;
			return;
		}

		int sign = 1;
		double temp[4][4];

		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				cofactor(A, temp, i, j, n);

				if ((i + j) % 2 == 0)
					sign = 1;
				else
					sign = -1;

				adj[j][i] = (sign)*(determinant(temp, n - 1));
			}
		}
	}

	matrix_4 matrix_4::inverse()
	{
		// Transform our matrix into double[4][4] form
		double contents[4][4];
		
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				contents[i][j] = data[i][j];
			}
		}

		// Find determinant
		double det = determinant(contents, 4);

		if (det == 0)
		{
			matrix_4 empty;
			printf("Can't find inverse as determinant is 0");
			return empty;
		}

		// Find adjointed matrix
		double adj[4][4];
		adjoint(contents, adj, 4);

		matrix_4 inverse;

		// Set the inverse matrix data to this matrix's data
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				inverse.data[i][j] = adj[i][j] / det;
			}
		}

		return inverse;
	}
}
