/*
 * ImageTransformation.h
 *
 *  Created on: Feb 25, 2015
 *      Author: rfsantacruz
 */

#ifndef IMAGETRANSFORMATION_IMAGETRANSFORMATION_H_
#define IMAGETRANSFORMATION_IMAGETRANSFORMATION_H_

#include "../entity/Image.h"
#include "../ImageFunctors/MinMaxScaleImgFunctor.h"
#include "../ImageOperations/PixelOperation.h"
#include "../ImageOperations/ImageOperation.h"
#include <math.h>
#include <functional>


class ImageTransformation{

private:
	//provide a private constructor and remove copy constructor
	//and assignment operation from singleton class
	ImageTransformation(){};
	ImageTransformation(ImageTransformation const&) = delete;
	void operator=(ImageTransformation const&) = delete;


public:

	static ImageTransformation& getInstance(){
		static ImageTransformation INSTANCE;
		return INSTANCE;
	}

	virtual ~ImageTransformation(){}

	template<typename T>
	Image<T> binarization(const Image<T>& img, T threshold, T pos=1, T neg=0){

		typename TypeDefs<T>::pixelTransformFunction lbin = [&threshold, &pos, &neg](T pixelValue) {

			int ret = pos;
			if(pixelValue < threshold)
				ret = neg;

			return static_cast<T>(ret);
		};

		PixelOperation<T> op(lbin);
		return op.execute(img);
	}

	template<typename T>
	Image<T> minMaxScaling(const Image<T>& img, T max=255, T min=0){

		MinMaxScaleImgFunctor<T> func(img, max, min);
		ImageOperation<T> op(func);

		return op.execute(img);
	}

};


#endif /* IMAGETRANSFORMATION_IMAGETRANSFORMATION_H_ */
