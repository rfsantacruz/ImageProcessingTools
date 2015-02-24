/*
 * WindowOperation.h
 *
 *  Created on: Feb 19, 2015
 *      Author: rfsantacruz
 */

#ifndef IMAGEOPERATIONS_WINDOWOPERATION_H_
#define IMAGEOPERATIONS_WINDOWOPERATION_H_

#include "../entity/Image.h"
#include "../masks/GenericConvolutionMask.h"

class WindowOperation {

private:
	GenericConvolutionMask& m_mask;

public:
	WindowOperation(GenericConvolutionMask& mask):m_mask(mask){}
	virtual ~WindowOperation(){}

	Image<int> execute(Image<int> src);
};

#endif /* IMAGEOPERATIONS_WINDOWOPERATION_H_ */
