#include "matrix_txt.h"

namespace math
{
	template<unsigned int N>
	void matrix_txt<N>::Init(float x1y1,
								float x2y1,
								float x1y2,
								float x2y2)
	{
		data = {	x1y1, x2y1,
					x1y2, x2y2 };
	}

	template<unsigned int N>
	void matrix_txt<N>::Init(float x1y1,
								float x2y1,
								float x3y1,
								float x1y2,
								float x2y2,
								float x3y2,
								float x1y3,
								float x2y3,
								float x3y3)
	{
		data = {	x1y1, x2y1, x3y1,
					x1y2, x2y2, x3y2, 
					x1y3, x2y3, x3y3 };
	}

	template<unsigned int N>
	void matrix_txt<N>::Init(float x1y1,
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
								float x4y4 )
	{
		data = {	x1y1, x2y1, x3y1, x4y1,
					x1y2, x2y2, x3y2, x4y2,
					x1y3, x2y3, x3y3, x4y3,
					x1y4, x2y4, x3y4, x4y4 };
	}

	template <unsigned int N> float matrix_txt<N>::det()
	{
		if (N == 4)
		{
			
		}
	}

}
