/*
 * ImageOperation.cpp
 *
 *  Created on: Feb 25, 2015
 *      Author: rfsantacruz
 */

#include "ImageOperation.h"

template<typename T>
Image<T> ImageOperation<T>::execute(Image<T> src) {
	Image<T> ret = src;

	m_imgFunctor.preprocessing(src);

	for (auto x = 0; x < src.getNHeight(); ++x) {
		for (auto y = 0; y < src.getNWidht(); ++y) {
			ret(x,y) = m_imgFunctor.compute(x,y);
		}
	}

	return ret;
}

//declare possible types
template class ImageOperation<uchar>;
template class ImageOperation<int>;
template class ImageOperation<float>;
template class ImageOperation<double>;

