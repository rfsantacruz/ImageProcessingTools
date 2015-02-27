/*
 * LaplacianMask.h
 *
 *  Created on: Feb 24, 2015
 *      Author: rfsantacruz
 */

#ifndef LAPLACIANMASK_H_
#define LAPLACIANMASK_H_

#include <math.h>

template<typename T>
class LaplacianMask: public GenericConvolutionMask<T>{

private:
	bool m_bdiagonal;
	T** m_akernel;

public:
	LaplacianMask(int nRadius, bool diagonal=true):GenericConvolutionMask<T>(nRadius),m_bdiagonal(diagonal){
		int length = (2* this->getNRadius()) + 1;
		m_akernel = new T*[length];

		for (auto x = 0; x < length; ++x) {
			m_akernel[x] = new T[length];
			for (auto y = 0; y < length; ++y) {
				if(m_bdiagonal){
					m_akernel[x][y] = -1;
				}else{
					if(x == this->getNRadius() || y == this->getNRadius()){
						m_akernel[x][y] = -1;
					}else{
						m_akernel[x][y] = 0;
					}
				}
			}
		}
		T centerValue = 0;
		for (auto x = 0; x < length; ++x) {
			for (auto y = 0; y < length; ++y) {
				if(m_akernel[x][y] == -1)
					centerValue++;
			}
		}
		m_akernel[this->getNRadius()][this->getNRadius()] = centerValue - 1;
	}

	virtual ~LaplacianMask(){
		int length = (2*this->getNRadius()) + 1;
		for (auto x = 0; x < length; ++x) {
			delete[] m_akernel[x];
		}
		delete m_akernel;

		m_akernel = nullptr;
	}

	virtual T compute(T** window) override{
		return this->convolute(window, m_akernel);
	}

};




#endif /* LAPLACIANMASK_H_ */
