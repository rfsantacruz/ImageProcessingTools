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

template<typename T>
class WindowOperation {

private:
	GenericConvolutionMask<T>& m_mask;

public:
	WindowOperation(GenericConvolutionMask<T>& mask):m_mask(mask){}
	virtual ~WindowOperation(){}

	Image<T> execute(Image<T> src);

	void setMask(GenericConvolutionMask<T>& mask){
		m_mask = mask;
	}
};

#endif /* IMAGEOPERATIONS_WINDOWOPERATION_H_ */
