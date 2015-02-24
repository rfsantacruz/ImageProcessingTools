/*
 * LaplacianMask.h
 *
 *  Created on: Feb 24, 2015
 *      Author: rfsantacruz
 */

#ifndef LAPLACIANMASK_H_
#define LAPLACIANMASK_H_

#include <math.h>

class LaplacianMask: public GenericConvolutionMask{

private:
	bool m_bdiagonal;
	int** m_akernel;

public:
	LaplacianMask(int nRadius, bool diagonal=true):GenericConvolutionMask(nRadius),m_bdiagonal(diagonal){
		int length = (2*getNRadius()) + 1;
		m_akernel = new int*[length];

		for (auto x = 0; x < length; ++x) {
			m_akernel[x] = new int[length];
			for (auto y = 0; y < length; ++y) {
				if(m_bdiagonal){
					m_akernel[x][y] = -1;
				}else{
					if(x == getNRadius() || y == getNRadius()){
						m_akernel[x][y] = -1;
					}else{
						m_akernel[x][y] = 0;
					}
				}
			}
		}
		int centerValue = 0;
		for (auto x = 0; x < length; ++x) {
			for (auto y = 0; y < length; ++y) {
				if(m_akernel[x][y] == -1)
					centerValue++;
			}
		}
		m_akernel[getNRadius()][getNRadius()] = centerValue;

	}

	virtual ~LaplacianMask(){
		int length = (2*getNRadius()) + 1;
		for (auto x = 0; x < length; ++x) {
			delete[] m_akernel[x];
		}
		delete m_akernel;
	}

	virtual int compute(int** window) override{
		return convolute(window, m_akernel);
	}

};




#endif /* LAPLACIANMASK_H_ */
