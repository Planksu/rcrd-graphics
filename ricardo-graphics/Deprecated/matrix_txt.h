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
		double data[N*N];


	public:

		// 2x2 init
		void Init(float x1y1, float x2y1, float x1y2, float x2y2);

		// 3x3 init
		void Init(	float x1y1,
					float x2y1,
					float x3y1,
					float x1y2,
					float x2y2,
					float x3y2,
					float x1y3,
					float x2y3,
					float x3y3);

		// 4x4 init
		void Init(	float x1y1,
					float x2y1, 
					float x3y1, 
					float x4y1, 
					float x1y2, 
					float x2y2, 
					float x3y2, 
					float x4y2, 
					float x1y3, 
					float x2y3, 
					float x3y3, 
					float x4y3, 
					float x1y4, 
					float x2y4, 
					float x3y4, 
					float x4y4 );

		float det();
	};

}

#endif