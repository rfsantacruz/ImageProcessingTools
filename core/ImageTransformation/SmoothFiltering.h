/*
 * WindowTransformation.h
 *
 *  Created on: Feb 19, 2015
 *      Author: rfsantacruz
 */

#ifndef IMAGETRANSFORMATION_SMOOTHFILTERING_H_
#define IMAGETRANSFORMATION_SMOOTHFILTERING_H_

#include "../entity/Image.h"
#include "../ImageOperations/WindowOperation.h"
#include "../masks/MeanMask.h"
#include "../masks/MedianMask.h"

class SmoothFiltering {

private:
	SmoothFiltering(){}
	SmoothFiltering(SmoothFiltering const&) = delete;
	void operator=(SmoothFiltering const&) = delete;

public:
	static SmoothFiltering& getInstance(){
		static SmoothFiltering INSTANCE;
		return INSTANCE;
	}
	virtual ~SmoothFiltering(){}

	template<typename T>
	Image<T> mean(const Image<T>& img, int radius){
		MeanMask<T> mask(radius);
		WindowOperation<T> op(mask);
		return op.execute(img);

	}

	template<typename T>
	Image<T> median(const Image<T>& img, int radius){
		MedianMask<T> mask(radius);
		WindowOperation<T> op(mask);
		return op.execute(img);

	}

};

#endif /* IMAGETRANSFORMATION_SMOOTHFILTERING_H_ */
