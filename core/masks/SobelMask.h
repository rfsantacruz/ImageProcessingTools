/*
 * LaplacianMask.h
 *
 *  Created on: Feb 24, 2015
 *      Author: rfsantacruz
 */

#ifndef SOBELMASK_H_
#define SOBELMASK_H_

template<typename T>
class SobelMask: public GenericConvolutionMask<T>{

private:
	bool m_bhorizontal;
	T** m_akernel;

public:
	SobelMask(int nRadius, bool horizontal=true):GenericConvolutionMask<T>(nRadius), m_bhorizontal(horizontal){

		//assert(getNRadius() == 3 || getNRadius() == 5);

		const int length = (2*this->getNRadius()) + 1;
		m_akernel = new T*[length];
		for (auto x = 0; x < length; ++x) {
			m_akernel[x] = new T[length];
		}

		if(this->getNRadius() == 3){
			if(m_bhorizontal){
				m_akernel[0][0]=-1;m_akernel[0][1]=-2;m_akernel[0][2]=-1;
				m_akernel[1][0]=0;m_akernel[1][1]=0;m_akernel[1][2]=0;
				m_akernel[2][0]=1;m_akernel[2][1]=2;m_akernel[2][2]=1;

			}else{
				m_akernel[0][0]=1;m_akernel[0][1]=0;m_akernel[0][2]=-1;
				m_akernel[1][0]=2;m_akernel[1][1]=0;m_akernel[1][2]=-2;
				m_akernel[2][0]=1;m_akernel[2][1]=0;m_akernel[2][2]=-1;
			}
		}else if(this->getNRadius() == 5){
			if(m_bhorizontal){
				m_akernel[0][0]=-1;m_akernel[0][1]=-4;m_akernel[0][2]=-6;m_akernel[0][3]=-4;m_akernel[0][4]=-1;
				m_akernel[1][0]=-2;m_akernel[1][1]=-8;m_akernel[1][2]=-12;m_akernel[1][3]=-8;m_akernel[1][4]=-2;
				m_akernel[2][0]=0;m_akernel[2][1]=0;m_akernel[2][2]=0;m_akernel[2][3]=0;m_akernel[2][4]=0;
				m_akernel[3][0]=2;m_akernel[3][1]=8;m_akernel[3][2]=12;m_akernel[3][3]=8;m_akernel[3][4]=2;
				m_akernel[4][0]=1;m_akernel[4][1]=4;m_akernel[4][2]=6;m_akernel[4][3]=4;m_akernel[4][4]=1;
			}else{
				m_akernel[0][0]=1;m_akernel[0][1]=2;m_akernel[0][2]=0;m_akernel[0][3]=-2;m_akernel[0][4]=-1;
				m_akernel[1][0]=4;m_akernel[1][1]=8;m_akernel[1][2]=0;m_akernel[1][3]=-8;m_akernel[1][4]=-4;
				m_akernel[2][0]=6;m_akernel[2][1]=12;m_akernel[2][2]=0;m_akernel[2][3]=-12;m_akernel[2][4]=-6;
				m_akernel[3][0]=4;m_akernel[3][1]=8;m_akernel[3][2]=0;m_akernel[3][3]=-8;m_akernel[3][4]=-4;
				m_akernel[4][0]=1;m_akernel[4][1]=2;m_akernel[4][2]=0;m_akernel[4][3]=-2;m_akernel[4][4]=-1;
			}
		}
	}

	virtual ~SobelMask(){
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





#endif /* SOBELMASK_H_ */
