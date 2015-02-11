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

	Image<int> negative(const Image<int>& img, int L=256);

	Image<int> logarithmic(const Image<int>& img, double C=1.0);

	Image<int> gamma(const Image<int>& img, double C=1.0, double Gama=0.4);

	Image<int> customTransform(const Image<int>& img, pixelTransformFunction lambda);
};

//it is a workaround to keep the implementation
//and the declaration separated when use template class.
//#include "PixelTransformation.cpp"

#endif /* IMAGETRANSFORMATION_PIXELTRANSFORMATION_H_ */
