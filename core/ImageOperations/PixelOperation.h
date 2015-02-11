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

typedef std::function<int(int)> pixelTransformFunction;

class PixelOperation {

private:
	pixelTransformFunction m_func;

public:

	PixelOperation(pixelTransformFunction func):m_func(func){}

	virtual ~PixelOperation(){}

	Image<int> execute(Image<int> src);
};

#endif /* IMAGEOPERATIONS_PIXELOPERATION_H_ */
