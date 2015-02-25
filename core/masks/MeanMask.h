/*
 * MeanMask.h
 *
 *  Created on: Feb 19, 2015
 *      Author: rfsantacruz
 */

#ifndef MEANMASK_H_
#define MEANMASK_H_

#include <math.h>

template<typename T>
class MeanMask : public GenericConvolutionMask<T>{

public:
	MeanMask(int radius):GenericConvolutionMask<T>(radius){}

	virtual ~MeanMask(){}

	virtual T compute(T** window) override{
		T sum = 0;

		for (int x = 0; x < (2*this->getNRadius()) + 1; x++) {
			for (int y = 0;  y < (2*this->getNRadius()) + 1; y++) {
				sum += window[x][y];
			}
		}

		double area = pow((2*this->getNRadius() + 1),2);
		return static_cast<int>(sum/area);
	}
};

#endif /* MEANMASK_H_ */
