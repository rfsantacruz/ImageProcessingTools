/*
 * PixelTransformation.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: rfsantacruz
 */

#include "PixelTransformation.h"
#include <math.h>

Image<int> PixelTransformation::negative(const Image<int>& img, int L) {

	pixelTransformFunction lNegative = [&L](int pixelValue) { return static_cast<int>((L - 1) - pixelValue); };

	PixelOperation op(lNegative);

	return op.execute(img);
}

Image<int> PixelTransformation::logarithmic(const Image<int>& img, double C) {

	pixelTransformFunction llogarithmic = [&C](int pixelValue) { return static_cast<int>(C * log(1 + pixelValue));};

	PixelOperation op(llogarithmic);

	return op.execute(img);
}

Image<int> PixelTransformation::gamma(const Image<int>& img, double C, double GAMMA) {

	pixelTransformFunction llogarithmic = [&C, &GAMMA](int pixelValue) { return static_cast<int>(C * pow(pixelValue,GAMMA));};

	PixelOperation op(llogarithmic);

	return op.execute(img);
}

Image<int> PixelTransformation::customTransform(const Image<int>& img, pixelTransformFunction lambda){

	PixelOperation op(lambda);

	return op.execute(img);

}

