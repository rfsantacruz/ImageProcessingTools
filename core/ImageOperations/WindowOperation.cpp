/*
 * WindowOperation.cpp
 *
 *  Created on: Feb 19, 2015
 *      Author: rfsantacruz
 */

#include "WindowOperation.h"

template<typename T>
Image<T> WindowOperation<T>::execute(Image<T> src){

	Image<T> ret = src;

	for (auto xCentral = m_mask.getNRadius(); xCentral < ret.getNHeight() - m_mask.getNRadius(); xCentral++) {
		for (auto yCentral = m_mask.getNRadius(); yCentral < ret.getNWidht() - m_mask.getNRadius(); yCentral++) {

			int xbegin = xCentral - m_mask.getNRadius();
			int xend = xCentral + m_mask.getNRadius();
			int ybegin = yCentral - m_mask.getNRadius();
			int yend = yCentral + m_mask.getNRadius();

			//transform image reference to value
			T** win = new T*[2*m_mask.getNRadius() + 1];
			T*** winRef = src(xbegin, xend, ybegin, yend);
			for (auto xwin = 0; xwin < 2*m_mask.getNRadius() + 1; ++xwin) {
				win[xwin] = new T[2*m_mask.getNRadius() + 1];
				for (auto ywin = 0; ywin < 2*m_mask.getNRadius() + 1; ++ywin) {
					win[xwin][ywin] = (*winRef[xwin][ywin]);
				}
			}

			//peform convolution
			ret(xCentral,yCentral) = m_mask.compute(win);

			//free space
			for (auto xwin = 0; xwin < 2*m_mask.getNRadius() + 1; ++xwin) {
				delete[] win[xwin];
			}
			delete win;
		}
	}

	return ret;
}

//declare possible types
template class WindowOperation<uchar>;
template class WindowOperation<int>;
template class WindowOperation<float>;
template class WindowOperation<double>;
