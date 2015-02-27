/*
 * PixelTransformation.h
 *
 *  Created on: Feb 9, 2015
 *      Author: rfsantacruz
 */

#ifndef IMAGETRANSFORMATION_PIXELTRANSFORMATION_H_
#define IMAGETRANSFORMATION_PIXELTRANSFORMATION_H_

#include "../entity/Image.h"
#include "../ImageOperations/PixelOperation.h"
#include "../entity/GlobalDefs.h"
#include <math.h>

//TODO Adapt template of transformation for Image<T> -> Image<U>

class PixelTransformation {

private:
	//provide a private constructor and remove copy constructor
	//and assignment operation from singleton class
	PixelTransformation(){};
	PixelTransformation(PixelTransformation const&) = delete;
	void operator=(PixelTransformation const&) = delete;


public:

	static PixelTransformation& getInstance(){
		static PixelTransformation INSTANCE;
		return INSTANCE;
	}

	virtual ~PixelTransformation(){}

	template <typename T>
	Image<T> negative(const Image<T>& img, int L=256);

	template <typename T>
	Image<T> logarithmic(const Image<T>& img, double C=1.0);

	template <typename T>
	Image<T> gamma(const Image<T>& img, double C=1.0, double Gama=0.4);

	template <typename T>
	Image<T> customTransform(const Image<T>& img, typename TypeDefs<T>::pixelTransformFunction lambda);

};

//template function must be defined in header files
template <typename T>
Image<T> PixelTransformation::negative(const Image<T>& img, int L) {

	typename TypeDefs<T>::pixelTransformFunction lNegative = [&L](int pixelValue) { return static_cast<T>((L - 1) - pixelValue); };

	PixelOperation<T> op(lNegative);

	return op.execute(img);
}

template <typename T>
Image<T> PixelTransformation::logarithmic(const Image<T>& img, double C) {

	typename TypeDefs<T>::pixelTransformFunction llogarithmic = [&C](int pixelValue) { return static_cast<T>(C * log(1 + pixelValue));};

	PixelOperation<T> op(llogarithmic);

	return op.execute(img);
}

template <typename T>
Image<T> PixelTransformation::gamma(const Image<T>& img, double C, double GAMMA) {

	typename TypeDefs<T>::pixelTransformFunction llogarithmic = [&C, &GAMMA](int pixelValue) { return static_cast<T>(C * pow(pixelValue,GAMMA));};

	PixelOperation<T> op(llogarithmic);

	return op.execute(img);
}

template <typename T>
Image<T> PixelTransformation::customTransform(const Image<T>& img, typename TypeDefs<T>::pixelTransformFunction lambda){

	PixelOperation<T> op(lambda);

	return op.execute(img);
}


#endif /* IMAGETRANSFORMATION_PIXELTRANSFORMATION_H_ */
