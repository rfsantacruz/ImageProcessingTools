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

	Image<int> mean(const Image<int>& img, int radius){
		MeanMask mask(radius);
		WindowOperation op(mask);
		return op.execute(img);

	}

	Image<int> median(const Image<int>& img, int radius){
		MedianMask mask(radius);
		WindowOperation op(mask);
		return op.execute(img);

	}

};

#endif /* IMAGETRANSFORMATION_SMOOTHFILTERING_H_ */
