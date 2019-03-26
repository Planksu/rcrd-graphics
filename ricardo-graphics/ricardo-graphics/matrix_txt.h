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
			double data1[2] = { x1y1, x2y1 };
			double data2[2] = { x1y2, x2y2 };

			std::copy(data1, data1 + 2, data[0]);
			std::copy(data1, data1 + 2, data[1]);
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

			std::copy(data1, data1 + 3, data[0]);
			std::copy(data2, data2 + 3, data[1]);
			std::copy(data3, data3 + 3, data[2]);
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

		template <unsigned int N = 4> float det()
		{
			return 
				data[0][3] * data[1][2] * data[2][1] * data[3][0] - data[0][2] * data[1][3] * data[2][1] * data[3][0] -
				data[0][3] * data[1][1] * data[2][2] * data[3][0] + data[0][1] * data[1][3] * data[2][2] * data[3][0] +
				data[0][2] * data[1][1] * data[2][3] * data[3][0] - data[0][1] * data[1][2] * data[2][3] * data[3][0] -
				data[0][3] * data[1][2] * data[2][0] * data[3][1] + data[0][2] * data[1][3] * data[2][0] * data[3][1] +
				data[0][3] * data[1][0] * data[2][2] * data[3][1] - data[0][0] * data[1][3] * data[2][2] * data[3][1] -
				data[0][2] * data[1][0] * data[2][3] * data[3][1] + data[0][0] * data[1][2] * data[2][3] * data[3][1] +
				data[0][3] * data[1][1] * data[2][0] * data[3][2] - data[0][1] * data[1][3] * data[2][0] * data[3][2] -
				data[0][3] * data[1][0] * data[2][1] * data[3][2] + data[0][0] * data[1][3] * data[2][1] * data[3][2] +
				data[0][1] * data[1][0] * data[2][3] * data[3][2] - data[0][0] * data[1][1] * data[2][3] * data[3][2] -
				data[0][2] * data[1][1] * data[2][0] * data[3][3] + data[0][1] * data[1][2] * data[2][0] * data[3][3] +
				data[0][2] * data[1][0] * data[2][1] * data[3][3] - data[0][0] * data[1][2] * data[2][1] * data[3][3] -
				data[0][1] * data[1][0] * data[2][2] * data[3][3] + data[0][0] * data[1][1] * data[2][2] * data[3][3];
		}

		template<unsigned int N = 4> void transpose()
		{
			double dataT[N][N];

			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 0; j < N; j++)
				{
					dataT[j][i] = data[i][j];
				}
			}

			for (size_t i = 0; i < N; i++)
			{
				std::copy(dataT[i], dataT[i] + N, data[i]);
			}
		}

		template<unsigned int N = 4> void inverse()
		{

		}
	};

}

#endif