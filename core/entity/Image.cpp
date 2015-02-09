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
int& Image::operator()(int nx, int ny){

	assert(m_adImageMatrix && (*m_adImageMatrix));
	assert(nx >= 0 && nx<m_nHeight && ny >= 0 && ny<m_nWidht);

	return m_adImageMatrix[nx][ny];


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

int*** Image::operator()(int nxBegin, int nxEnd, int nyBegin, int nyEnd ){

	assert(m_adImageMatrix && (*m_adImageMatrix));

	assert(nxBegin < nxEnd);
	assert(nxBegin >= 0 && nxBegin < m_nHeight);
	assert(nxEnd >= 0 && nxBegin < m_nHeight);

	assert(nyBegin < nyEnd);
	assert(nyBegin >= 0 && nyBegin < m_nWidht);
	assert(nyEnd >= 0 && nyBegin < m_nWidht);

	int nSliceHeight = (nxEnd - nxBegin) + 1;
	int nSliceWidht = (nyEnd - nyBegin) + 1;

	int*** ret = new int**[nSliceHeight];
	for (auto x = 0; x < nSliceHeight; ++x) {
		ret[x] = new int*[nSliceWidht];
		for (auto y = 0; y < nSliceWidht; ++y) {
			ret[x][y] = &m_adImageMatrix[x + nxBegin][y + nyBegin];
		}
	}

	return ret;
}

bool Image::save(const std::string& targetPath, ImageFileFormat eFormat /*=ImageFileFormat::PNG*/){


	boost::filesystem::path p(targetPath);
	boost::filesystem::path newExt(EnumUtil::imFFormatEnum2Str(eFormat));
	p.replace_extension(newExt);

	uchar ret[m_nHeight][m_nWidht];
	for (int x = 0; x < m_nHeight; ++x) {
		for (int y = 0; y < m_nWidht; ++y) {
			ret[x][y] = static_cast<uchar>(m_adImageMatrix[x][y]);
		}
	}
	cv::Mat cmatTemp = cv::Mat(m_nHeight, m_nWidht, CV_8UC1, &ret);



	return cv::imwrite(p.string(), cmatTemp);

}

void Image::show(const std::string& windowName /*="Display Image"*/){

	uchar ret[m_nHeight][m_nWidht];
	for (int x = 0; x < m_nHeight; ++x) {
		for (int y = 0; y < m_nWidht; ++y) {
				ret[x][y] = static_cast<uchar>(m_adImageMatrix[x][y]);
		}
	}

	cv::Mat cmatTemp = cv::Mat(m_nHeight, m_nWidht, CV_8UC1, &ret);
	cv::namedWindow(windowName, CV_WINDOW_AUTOSIZE );
	cv::imshow(windowName, cmatTemp );
	cv::waitKey(0);
}

void Image::print(){
	if(m_adImageMatrix){
		for (auto x = 0; x < m_nHeight; ++x) {
			for (auto y = 0; y < m_nWidht; ++y) {
				std::cout << m_adImageMatrix[x][y]<< '\t';
			}
			std::cout << std::endl;
		}
	}
}

std::map<int,int> Image::histogram(){

	std::map<int,int> grayScaleFreq;

	for (auto y = 0; y < m_nHeight; ++y) {
		for (auto x = 0; x < m_nWidht; ++x) {
			int value = m_adImageMatrix[y][x];
			if(grayScaleFreq.find(value) == grayScaleFreq.end())
				grayScaleFreq[value] =  1;
			else
				grayScaleFreq[value] = grayScaleFreq[value] + 1;
		}
	}

	return grayScaleFreq;
}

