/*
 * Image.cpp
 *
 *  Created on: Dec 30, 2014
 *      Author: rfsantacruz
 */

#include "Image.h"

Image operator+(const Image& cIm){
	assert(cIm.m_adImageMatrix && (*cIm.m_adImageMatrix));
	return cIm;
}

Image operator+(double dCte, const Image& cImRight){

	Image ret = cImRight;

	assert(ret.m_adImageMatrix && (*ret.m_adImageMatrix));

	for(auto y = 0 ; y < ret.m_nHeight ; y++){
		for (auto x = 0; x < ret.m_nWidht; ++x) {
			ret.m_adImageMatrix[y][x] += dCte;
		}
	}
	return (ret);
}

Image operator+(const Image& cImLeft, double dCte){
		return dCte + cImLeft;
}


Image operator+(const Image& cImLeft, const Image& cImRight){

	Image ret = cImLeft;

	assert(ret.m_adImageMatrix && (*ret.m_adImageMatrix));
	assert(cImRight.m_adImageMatrix && (*cImRight.m_adImageMatrix));
	assert(cImRight.m_nHeight == ret.m_nHeight && cImRight.m_nWidht == ret.m_nWidht);

	for(auto y = 0 ; y < ret.m_nHeight ; y++){
		for (auto x = 0; x < ret.m_nWidht; ++x) {
			ret.m_adImageMatrix[y][x] += cImRight.m_adImageMatrix[y][x];
		}
	}
	return ret;
}

Image operator-(const Image& cIm){

	Image ret = cIm;

	assert(ret.m_adImageMatrix && (*ret.m_adImageMatrix));
	for(auto y = 0 ; y < ret.m_nHeight ; y++){
		for (auto x = 0; x < ret.m_nWidht; ++x) {
			ret.m_adImageMatrix[y][x] = -ret.m_adImageMatrix[y][x];
		}
	}

	return ret;
}

Image operator-(const Image& cImLeft, double dCte){
	Image ret = cImLeft;

	assert(ret.m_adImageMatrix && (*ret.m_adImageMatrix));

	for(auto y = 0 ; y < ret.m_nHeight ; y++){
		for (auto x = 0; x < ret.m_nWidht; ++x) {
			ret.m_adImageMatrix[y][x] -= dCte;
		}
	}
	return (ret);
}

Image operator-(double dCte, const Image& cImRight){
	return cImRight + dCte;
}

Image operator-(const Image& cImLeft, const Image& cImRight){

	Image ret = cImLeft;

	assert(ret.m_adImageMatrix && (*ret.m_adImageMatrix));
	assert(cImRight.m_adImageMatrix && (*cImRight.m_adImageMatrix));
	assert(cImRight.m_nHeight == ret.m_nHeight && cImRight.m_nWidht == ret.m_nWidht);

	for(auto y = 0 ; y < ret.m_nHeight ; y++){
		for (auto x = 0; x < ret.m_nWidht; ++x) {
			ret.m_adImageMatrix[y][x] -= cImRight.m_adImageMatrix[y][x];
		}
	}
	return ret;
}

Image operator*(const Image& cImLeft, const Image& cImRight){

	Image ret = cImLeft;

	assert(ret.m_adImageMatrix && (*ret.m_adImageMatrix));
	assert(cImRight.m_adImageMatrix && (*cImRight.m_adImageMatrix));
	assert(cImRight.m_nHeight == ret.m_nHeight && cImRight.m_nWidht == ret.m_nWidht);

	for(auto y = 0 ; y < ret.m_nHeight ; y++){
		for (auto x = 0; x < ret.m_nWidht; ++x) {
			ret.m_adImageMatrix[y][x] *= cImRight.m_adImageMatrix[y][x];
		}
	}
	return ret;
}


Image operator*(const Image& cImLeft, double dCte){
	Image ret = cImLeft;

	assert(ret.m_adImageMatrix && (*ret.m_adImageMatrix));

	for(auto y = 0 ; y < ret.m_nHeight ; y++){
		for (auto x = 0; x < ret.m_nWidht; ++x) {
			ret.m_adImageMatrix[y][x] *= dCte;
		}
	}
	return (ret);
}

Image operator*(double dCte, const Image& cImRight){
	return cImRight + dCte;
}

Image operator/(const Image& cImLeft, const Image& cImRight){
	Image ret = cImLeft;

	assert(ret.m_adImageMatrix && (*ret.m_adImageMatrix));
	assert(cImRight.m_adImageMatrix && (*cImRight.m_adImageMatrix));
	assert(cImRight.m_nHeight == ret.m_nHeight && cImRight.m_nWidht == ret.m_nWidht);

	for(auto y = 0 ; y < ret.m_nHeight ; y++){
		for (auto x = 0; x < ret.m_nWidht; ++x) {
			ret.m_adImageMatrix[y][x] /= cImRight.m_adImageMatrix[y][x];
		}
	}
	return ret;
}

Image operator/(const Image& cImLeft, double dCte){
	Image ret = cImLeft;

	assert(ret.m_adImageMatrix && (*ret.m_adImageMatrix));

	for(auto y = 0 ; y < ret.m_nHeight ; y++){
		for (auto x = 0; x < ret.m_nWidht; ++x) {
			ret.m_adImageMatrix[y][x] /= dCte;
		}
	}
	return (ret);
}

Image operator/(double dCte, const Image& cImRight){
	return cImRight + dCte;
}


//slice operation
int* Image::operator()(int ny, int nx){

	assert(m_adImageMatrix && (*m_adImageMatrix));
	assert(ny >= 0 && ny<m_nHeight && ny >= 0 && nx<m_nWidht);

	return &m_adImageMatrix[ny][nx];


}

int** Image::operator()(int nId, bool bisRow){

	assert(m_adImageMatrix && (*m_adImageMatrix));
	int** ret = nullptr;

	if(bisRow){
		assert(nId >= 0 && nId < m_nHeight);
		ret = new int*[m_nWidht];
		for (auto x = 0; x < m_nWidht; ++x)
			ret[x] = &m_adImageMatrix[nId][x];
	}else{
		assert(nId >= 0 && nId < m_nWidht);
		ret = new int*[m_nHeight];
		for (auto y = 0; y < m_nHeight; ++y)
			ret[y] = &m_adImageMatrix[y][nId];
	}

	return ret;
}

int*** Image::operator()(int nyBegin, int nyEnd, int nxBegin, int nxEnd ){

	assert(m_adImageMatrix && (*m_adImageMatrix));

	assert(nyBegin > nyEnd);
	assert(nyBegin >= 0 && nyBegin < m_nHeight);
	assert(nyEnd >= 0 && nyBegin < m_nHeight);

	assert(nxBegin > nxEnd);
	assert(nxBegin >= 0 && nxBegin < m_nWidht);
	assert(nxEnd >= 0 && nxBegin < m_nWidht);

	int nSliceHeight = (nyEnd - nyBegin) + 1;
	int nSliceWidht = (nxEnd - nxBegin) + 1;

	int*** ret = new int**[nSliceHeight];
	for (auto y = 0; y < nSliceHeight; ++y) {
		ret[y] = new int*[nSliceWidht];
		for (auto x = 0; x < nSliceWidht; ++x) {
			ret[y][x] = &m_adImageMatrix[y][x];
		}
	}

	return ret;
}

bool Image::save(const std::string& targetPath, ImageFileFormat eFormat /*=ImageFileFormat::PNG*/){


	boost::filesystem::path p(targetPath);
	boost::filesystem::path newExt(EnumUtil::imFFormatEnum2Str(eFormat));
	p.replace_extension(newExt);

	cv::Mat cmatTemp = cv::Mat(m_nHeight, m_nWidht, CV_8UC1, (*m_adImageMatrix));
	return cv::imwrite(p.string(), cmatTemp);

}

void Image::show(const std::string& windowName /*="Display Image"*/){
	cv::Mat cmatTemp = cv::Mat(m_nHeight, m_nWidht, CV_8UC1, (*m_adImageMatrix));
	cv::namedWindow(windowName, CV_WINDOW_AUTOSIZE );
	cv::imshow(windowName, cmatTemp );
	cv::waitKey(0);
}

std::map<int,int> Image::histogram(){
	//TODO Implement histogram computation
	std::map<int,int> grayScaleFreq;

	for (auto y = 0; y < m_nHeight; ++y) {
		for (auto x = 0; x < m_nWidht; ++x) {
			int value = m_adImageMatrix[y][x];
			if(grayScaleFreq.find(value) != grayScaleFreq.end())
				grayScaleFreq[value] =  1;
			else
				grayScaleFreq[value] = grayScaleFreq[value] + 1;
		}
	}

	return grayScaleFreq;
}

