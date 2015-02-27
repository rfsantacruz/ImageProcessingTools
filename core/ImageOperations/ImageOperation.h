/*
 * ImageOperation.h
 *
 *  Created on: Feb 25, 2015
 *      Author: rfsantacruz
 */

#ifndef IMAGEOPERATIONS_IMAGEOPERATION_H_
#define IMAGEOPERATIONS_IMAGEOPERATION_H_

#include "../ImageFunctors/GenericImageFunctor.h"
#include "../entity/Image.h"

template<typename T>
class ImageOperation {

private:
	GenericImageFunctor<T>& m_imgFunctor;

public:
	ImageOperation(GenericImageFunctor<T>& func):m_imgFunctor(func){}
	virtual ~ImageOperation(){}
	Image<T> execute(Image<T> src);

};

#endif /* IMAGEOPERATIONS_IMAGEOPERATION_H_ */
