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

template<typename T>
class MedianMask: public GenericConvolutionMask<T>{

public:
	MedianMask(int nRadius):GenericConvolutionMask<T>(nRadius){}

	virtual ~MedianMask(){}

	virtual T compute(T** window) override{
		int pixelArea = pow((2*this->getNRadius() + 1),2);
		std::vector<T> pixels(pixelArea);
		int idx = 0;

		for (int x = 0; x < (2*this->getNRadius()) + 1; x++) {
			for (int y = 0;  y < (2*this->getNRadius()) + 1; y++) {
				idx = y + (x * ((2*this->getNRadius()) + 1));
				pixels[idx] = window[x][y];
			}
		}
		std::sort(pixels.begin(), pixels.end());
		idx = this->getNRadius() + (this->getNRadius() * ((2*this->getNRadius()) + 1));
		return static_cast<T>(pixels[idx]);
	}


};



#endif /* MEDIANMASK_H_ */
