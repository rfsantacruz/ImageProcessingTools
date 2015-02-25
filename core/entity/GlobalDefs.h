/*
 * structs.h
 *
 *  Created on: Dec 30, 2014
 *      Author: rfsantacruz
 */

#ifndef GLOBALDEFS_H_
#define GLOBALDEFS_H_

#include <functional>

enum class ImageFileFormat
{
	JPEG,
	PNG,
	BMP,
	NOT_ACCEPTED
};

enum class ESobel{
	Horizontal,
	Vertical,
	Absolute
};

//list of defs
template<typename T>
struct TypeDefs
{
	typedef std::function<T(T)> pixelTransformFunction;
};

//list of instantiations




#endif /* GLOBALDEFS_H_ */
