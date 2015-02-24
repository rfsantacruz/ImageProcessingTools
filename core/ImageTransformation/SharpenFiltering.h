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

	Image<int> laplacian(const Image<int>& img, int radius, bool diag=true){
		LaplacianMask mask(radius, diag);
		WindowOperation op(mask);
		return op.execute(img);
	}

	//TODO: implement sobel for x y and magnitude
	/*Image<int> sobel(const Image<int>& img, int radius, bool horizontal=true){

	}
*/

};

#endif /* IMAGETRANSFORMATION_SHARPENFILTERING_H_ */
