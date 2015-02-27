/*
 * MinMaxScaleImgFunctor.h
 *
 *  Created on: Feb 25, 2015
 *      Author: rfsantacruz
 */

#ifndef IMAGEFUNCTORS_MINMAXSCALEIMGFUNCTOR_H_
#define IMAGEFUNCTORS_MINMAXSCALEIMGFUNCTOR_H_

#include "GenericImageFunctor.h"

template<typename T>
class MinMaxScaleImgFunctor: public GenericImageFunctor<T>{

private:

	T m_maxNew;
	T m_minNew;
	T m_maxFound;
	T m_minFound;

public:
	MinMaxScaleImgFunctor(const Image<T>& inputImg, T maxNew, T minNew)
	:GenericImageFunctor<T>(inputImg),m_maxNew(maxNew),m_minNew(minNew),m_maxFound(-1000), m_minFound(1000){}

	virtual ~MinMaxScaleImgFunctor(){}

	virtual T compute(int x, int y) override{
		T pixel = this->getImgInput()(x,y);
		double a = (pixel - m_minFound)/static_cast<float>(m_maxFound - m_minFound);
		double newRange = m_maxNew - m_minNew;
		return  static_cast<T>(a * newRange )+ m_minNew;

	}

	virtual void preprocessing(Image<T>& input) override{
		GenericImageFunctor<T>::preprocessing(input);
		for (auto x = 0; x < this->getImgInput().getNHeight(); ++x){
			for (auto y = 0; y < this->getImgInput().getNWidht(); ++y){
				int pixel = this->getImgInput()(x,y);

				if(pixel > m_maxFound)
					m_maxFound = pixel;
				if(pixel < m_minFound)
					m_minFound = pixel;
			}
		}
	}


};

#endif /* IMAGEFUNCTORS_MINMAXSCALEIMGFUNCTOR_H_ */
