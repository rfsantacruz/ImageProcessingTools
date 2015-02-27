/*
 * GenericImageFunctor.h
 *
 *  Created on: Feb 25, 2015
 *      Author: rfsantacruz
 */

#ifndef IMAGEFUNCTORS_GENERICIMAGEFUNCTOR_H_
#define IMAGEFUNCTORS_GENERICIMAGEFUNCTOR_H_

#include "../entity/Image.h"

template<typename T>
class GenericImageFunctor {

private:
	Image<T>* m_imgInput;

public:
	GenericImageFunctor(Image<T> img):m_imgInput(&img){}

	virtual ~GenericImageFunctor(){}
	virtual T compute(int x, int y)=0;
	virtual void preprocessing(Image<T>& input){
		m_imgInput = &input;
	}

	Image<T>& getImgInput() const {
		return (*m_imgInput);
	}
};

#endif /* IMAGEFUNCTORS_GENERICIMAGEFUNCTOR_H_ */
