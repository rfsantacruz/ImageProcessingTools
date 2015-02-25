/*
 * PixelOperation.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: rfsantacruz
 */

#include "PixelOperation.h"

template<typename T>
Image<T> PixelOperation<T>::execute(Image<T> src){
	Image<T> ret = src;

	for (auto x = 0; x < ret.getNHeight(); ++x) {
		for (auto y = 0; y < ret.getNWidht(); ++y) {
			ret(x,y) = m_func(ret(x,y));
		}
	}
	return ret;
}
template<typename T>
void PixelOperation<T>::setFunc(const typename TypeDefs<T>::pixelTransformFunction& func) {
		m_func = func;
}

//declare possible types
template class PixelOperation<uchar>;
template class PixelOperation<int>;
template class PixelOperation<float>;
template class PixelOperation<double>;




