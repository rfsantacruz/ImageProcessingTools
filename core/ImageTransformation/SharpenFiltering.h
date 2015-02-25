/*
 * WindowTransformation.h
 *
 *  Created on: Feb 19, 2015
 *      Author: rfsantacruz
 */

#ifndef IMAGETRANSFORMATION_SHARPENFILTERING_H_
#define IMAGETRANSFORMATION_SHARPENFILTERING_H_

#include "../entity/Image.h"
#include "../ImageOperations/WindowOperation.h"
#include "../masks/LaplacianMask.h"
#include "../masks/SobelMask.h"
#include <math.h>
#include "../entity/GlobalDefs.h"
#include "../ImageOperations/PixelOperation.h"

class SharpenFiltering {

private:
	SharpenFiltering(){}
	SharpenFiltering(SharpenFiltering const&) = delete;
	void operator=(SharpenFiltering const&) = delete;

public:
	static SharpenFiltering& getInstance(){
		static SharpenFiltering INSTANCE;
		return INSTANCE;
	}
	virtual ~SharpenFiltering(){}

	template<typename T>
	Image<T> laplacian(const Image<T>& img, int radius, bool diag=true){
		LaplacianMask<T> mask(radius, diag);
		WindowOperation<T> op(mask);
		return op.execute(img);
	}

	template<typename T>
	Image<T> sobel(const Image<T>& img, int radius, ESobel type=ESobel::Absolute){

		SobelMask<T> HMask(radius, true);
		SobelMask<T> VMask(radius, false);

		if(type == ESobel::Horizontal){
			WindowOperation<T> maskop(HMask);
			Image<T> xsobel = maskop.execute(img);
			return xsobel;

		}else if(type == ESobel::Vertical){
			WindowOperation<T> maskop(VMask);
			Image<T> ysobel = maskop.execute(img);
			return ysobel;

		}else{
			typename TypeDefs<T>::pixelTransformFunction labs = [](T pixelValue) { return static_cast<T>(abs(pixelValue)); };
			PixelOperation<T> pixelop(labs);

			WindowOperation<T> maskop(HMask);
			Image<T> xsobel = pixelop.execute(maskop.execute(img));

			maskop.setMask(VMask);
			Image<T> ysobel = pixelop.execute(maskop.execute(img));

			return xsobel + ysobel;
		}
	}
};

#endif /* IMAGETRANSFORMATION_SHARPENFILTERING_H_ */
