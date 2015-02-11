/*
 * PixelOperation.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: rfsantacruz
 */

#include "PixelOperation.h"

Image<int> PixelOperation::execute(Image<int> src){
	Image<int> ret = src;

	for (auto x = 0; x < ret.getNHeight(); ++x) {
		for (auto y = 0; y < ret.getNWidht(); ++y) {
			ret(x,y) = m_func(ret(x,y));
		}
	}
	return ret;
}

