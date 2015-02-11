/*
 * PixelOperation.h
 *
 *  Created on: Feb 9, 2015
 *      Author: rfsantacruz
 */

#ifndef IMAGEOPERATIONS_PIXELOPERATION_H_
#define IMAGEOPERATIONS_PIXELOPERATION_H_

#include "../entity/Image.h"
#include <math.h>
#include <functional>
#include "../entity/GlobalDefs.h"

template <typename T>
class PixelOperation {

private:
	typename TypeDefs<T>::pixelTransformFunction m_func;

public:

	PixelOperation(typename TypeDefs<T>::pixelTransformFunction func):m_func(func){}

	virtual ~PixelOperation(){}

	Image<T> execute(Image<T> src);
};

#endif /* IMAGEOPERATIONS_PIXELOPERATION_H_ */
