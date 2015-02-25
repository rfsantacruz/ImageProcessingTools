/*
 * GenericMask.h
 *
 *  Created on: Feb 19, 2015
 *      Author: rfsantacruz
 */

#ifndef GENERICCONVOLUTIONMASK_H_
#define GENERICCONVOLUTIONMASK_H_

template<typename T>
class GenericConvolutionMask {
private:
	int m_nRadius;

public:
	GenericConvolutionMask(int radius):m_nRadius(radius){}

	virtual ~GenericConvolutionMask(){}

	//virtual abstract function
	virtual T compute(T** window)=0;

	T convolute(T** window, T** kernel){
		T sum = 0;

		for (int x = 0; x < (2*getNRadius()) + 1; x++) {
			for (int y = 0;  y < (2*getNRadius()) + 1; y++) {
				sum += kernel[x][y] * window[x][y];
			}
		}

		return static_cast<T>(sum);
	}

	int getNRadius() const {
		return m_nRadius;
	}

};

#endif /* GENERICCONVOLUTIONMASK_H_ */
