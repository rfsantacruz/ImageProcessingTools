/*
 * MeanMask.h
 *
 *  Created on: Feb 19, 2015
 *      Author: rfsantacruz
 */

#ifndef MEANMASK_H_
#define MEANMASK_H_

#include <math.h>

class MeanMask : public GenericConvolutionMask {

public:
	MeanMask(int radius):GenericConvolutionMask(radius){}

	virtual ~MeanMask(){}

	virtual int compute(int** window) override{
		int sum = 0;

		for (int x = 0; x < (2*getNRadius()) + 1; x++) {
			for (int y = 0;  y < (2*getNRadius()) + 1; y++) {
				sum += window[x][y];
			}
		}

		double area = pow((2*getNRadius() + 1),2);
		return sum/area;
	}
};

#endif /* MEANMASK_H_ */
