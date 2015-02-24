/*
 * MedianMask.h
 *
 *  Created on: Feb 24, 2015
 *      Author: rfsantacruz
 */

#ifndef MEDIANMASK_H_
#define MEDIANMASK_H_

#include <vector>
#include <algorithm>

class MedianMask: public GenericConvolutionMask{

public:
	MedianMask(int nRadius):GenericConvolutionMask(nRadius){}

	virtual ~MedianMask(){}

	virtual int compute(int** window) override{
		int pixelArea = pow((2*getNRadius() + 1),2);
		std::vector<int> pixels(pixelArea);
		int idx = 0;

		for (int x = 0; x < (2*getNRadius()) + 1; x++) {
			for (int y = 0;  y < (2*getNRadius()) + 1; y++) {
				idx = y + (x * ((2*getNRadius()) + 1));
				pixels[idx] = window[x][y];
			}
		}
		std::sort(pixels.begin(), pixels.end());
		idx = getNRadius() + (getNRadius() * ((2*getNRadius()) + 1));
		return pixels[idx];
	}


};



#endif /* MEDIANMASK_H_ */
