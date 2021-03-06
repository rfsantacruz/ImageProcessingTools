/*
 * constants.h
 *
 *  Created on: Dec 30, 2014
 *      Author: rfsantacruz
 */

#ifndef UTIL_H_
#define UTIL_H_
#include <string>
#include <boost/filesystem.hpp>
#include "GlobalDefs.h"

class EnumUtil{

public:
	static ImageFileFormat str2ImFFormatEnum(const std::string& strPath){

		ImageFileFormat ret = ImageFileFormat::NOT_ACCEPTED;

		if(!strPath.empty()){
			boost::filesystem::path p(strPath);
			std::string ext = p.extension().string();

			if(ext == ".jpg")
				ret = ImageFileFormat::JPEG;
			if(ext == ".png")
				ret = ImageFileFormat::PNG;
			if(ext == ".bmp")
				ret = ImageFileFormat::BMP;
		}

		return ret;

	}

	static std::string imFFormatEnum2Str(const ImageFileFormat& eImFileFormat ){

		std::string ret = ".png";

		switch (eImFileFormat) {
		case ImageFileFormat::PNG:
			ret= ".png";
			break;
		case ImageFileFormat::JPEG:
			ret = ".jpg";
			break;
		case ImageFileFormat::BMP:
			ret = ".bmp";
			break;
		default:
			ret = ".png";
			break;
		}

		return ret;

	}
};


#endif /* UTIL_H_ */
