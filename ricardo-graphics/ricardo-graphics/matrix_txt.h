#ifndef _MATRIX_TXT_H
#define _MATRIX_TXT_H

namespace math
{
	template <unsigned int N>
	class matrix_txt
	{
	public:
		matrix_txt() {};
		~matrix_txt() {};

	public:
		double data[N][N];


	public:

		template<unsigned int N = 2>
		void Init(double x1y1,
			double x2y1,
			double x1y2,
			double x2y2)
		{
			data = { { x1y1, x2y1 },
			{ x1y2, x2y2 }
			};
		}

		template<unsigned int N = 3>
		void Init(float x1y1,
			double x2y1,
			double x3y1,
			double x1y2,
			double x2y2,
			double x3y2,
			double x1y3,
			double x2y3,
			double x3y3)
		{
			double data1[3] = { x1y1, x2y1, x3y1 };
			double data2[3] = { x1y2, x2y2, x3y2 };
			double data3[3] = { x1y3, x2y3, x3y3 };

			std::copy(data1, data1 + 4, data[0]);
			std::copy(data2, data2 + 4, data[1]);
			std::copy(data3, data3 + 4, data[2]);
			std::copy(data4, data4 + 4, data[3]);
		}

		template<unsigned int N = 4>
		void Init(float x1y1,
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


		float det2x2(matrix_txt<2> m)
		{
			return ((m.data[0][0] * m.data[1][1]) - (m.data[1][0] * m.data[0][1]));
		}

		
		template <unsigned int N = 4> float det(matrix_txt<N> A)
		{
			matrix_txt<N> minor;
			int i, j, k, c1, c2;
			float determinant;
			int c[N];
			int O = 1;

			determinant = 0;
			if (N == 2)
			{
				determinant = ((data[0][0] * data[1][1]) - (data[1][0] * data[0][1]));
			}
			else
			{
				for (size_t i = 0; i < N; i++)
				{
					c1 = 0;
					c2 = 0;
					for (size_t j = 0; j < N; j++)
					{
						for (size_t k = 0; k < N; k++)
						{
							if (j != 0 && k != i)
							{
								minor.data[c1][c2] = A.data[j][k];
								c2++;
								if (c2 > N - 2)
								{
									c1++;
									c2 = 0;
								}
							}
						}
					}
					determinant = determinant + O * (A.data[0][i] * this->det(minor));
					O = -1 * O;
				}
			}
			return determinant;
		}
	};

}

#endif