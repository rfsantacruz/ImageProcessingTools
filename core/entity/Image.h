/*
 * Image.h
 *
 *  Created on: Dec 30, 2014
 *      Author: rfsantacruz
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include <string>
#include "constants.h"
#include "structs.h"
#include <cv.h>
#include <highgui.h>
#include <boost/filesystem.hpp>

//TODO: Review concepts and implementation of each function

template <class T>
class Image{
private:

	std::string m_strOriginalPath;
	int m_nWidht;
	int m_nHeight;
	ImageFileFormat m_eImageFileFormat;
	T** m_adImageMatrix;

public:
	//constructor and destructors
	Image(const std::string& strPath):m_strOriginalPath(strPath){

		cv::Mat cvImage;
		cvImage = cv::imread(strPath ,CV_LOAD_IMAGE_GRAYSCALE);

		m_nHeight = cvImage.rows;
		m_nWidht = cvImage.cols;

		m_eImageFileFormat = EnumUtil::str2ImFFormatEnum(strPath);

		m_adImageMatrix = new T*[m_nHeight];
		for (int x = 0; x < m_nHeight; ++x) {
			m_adImageMatrix[x] = new T[m_nWidht];
			for (int y = 0; y < m_nWidht; ++y) {
				m_adImageMatrix[x][y] = static_cast<T>(cvImage.at<uchar>(x,y));
			}
		}


	}

	Image(int nHeight=100, int nWidth=100, T unValue=0, ImageFileFormat eImgFileFormat=ImageFileFormat::PNG)
	:m_strOriginalPath(""), m_nWidht(nWidth), m_nHeight(nHeight),m_eImageFileFormat(eImgFileFormat){

		m_adImageMatrix = new T*[m_nHeight];
		for (int x = 0; x < m_nHeight; ++x) {
			m_adImageMatrix[x] = new T[m_nWidht];
			for (int y = 0; y < m_nWidht; ++y) {
				m_adImageMatrix[x][y] = unValue;
			}
		}

	}

	//copy constructor
	Image(const Image<T>& src):m_strOriginalPath(src.getStrOriginalPath()), m_nWidht(src.getNWidht()),
			m_nHeight(src.getNHeight()),m_eImageFileFormat(src.getEImageFileFormat()){

		m_adImageMatrix = new T*[m_nHeight];
		for (int x = 0; x < m_nHeight; ++x) {
			m_adImageMatrix[x] = new T[m_nWidht];
			for (int y = 0; y < m_nWidht; ++y) {
				m_adImageMatrix[x][y] = src.m_adImageMatrix[x][y];
			}
		}
	}

	virtual ~Image(){

		for (int x = 0; x < this->m_nHeight; ++x)
			delete[] m_adImageMatrix[x];

		delete[] m_adImageMatrix;

		m_adImageMatrix = nullptr;

	}

	//overloading operators as non members function
	template <class U>
	friend Image<U> operator+(const Image<U>& cIm);
	template <class U>
	friend Image<U> operator+(const Image<U>& cLeft ,const Image<U>& cRight);
	template <class U>
	friend Image<U> operator+(const Image<U>& cLeft, U dCte);
	template <class U>
	friend Image<U> operator+(U dCte, const Image<U>& cRight);

	template <class U>
	friend Image<U> operator-(const Image<U>& cIm);
	template <class U>
	friend Image<U> operator-(const Image<U>& cLeft, const Image<U>& cRight);
	template <class U>
	friend Image<U> operator-(const Image<U>& cLeft , U dCte);
	template <class U>
	friend Image<U> operator-(U dCte, const Image<U>& cRight);

	template <class U>
	friend Image<U> operator*(const Image<U>& cLeft, const Image<U>& cRight);
	template <class U>
	friend Image<U> operator*(const Image<U>& cLeft, U dCte);
	template <class U>
	friend Image<U> operator*(U dCte, const Image<U>& cRight);

	template <class U>
	friend Image<U> operator/(const Image<U>& cLeft, const Image<U>& cRight);
	template <class U>
	friend Image<U> operator/(const Image<U>& cLeft, U dCte);
	template <class U>
	friend Image<U> operator/(U dCte, const Image<U>& cRight);

	//slice operation overload as member function
	T& operator()(int nx, int ny);
	T** operator()(int nId, bool bisRow);
	T*** operator()(int nxBegin, int nxEnd, int nyBegin, int nyEnd);

	//members functions
	bool save(const std::string& targetPath, ImageFileFormat eFormat=ImageFileFormat::PNG);
	void show(const std::string& windowName="Display Image");
	void print();
	std::map<T,int> histogram();

	//getters and setters
	int getNHeight() const {
		return m_nHeight;
	}
	void setNHeight(int nHeight) {
		m_nHeight = nHeight;
	}
	int getNWidht() const {
		return m_nWidht;
	}
	void setNWidth(int nWidth){
		m_nWidht = nWidth;
	}
	const std::string& getStrOriginalPath() const {
		return m_strOriginalPath;
	}
	void setStrOriginalPath(const std::string& strOriginalPath) {
		m_strOriginalPath = strOriginalPath;
	}
	ImageFileFormat getEImageFileFormat() const {
		return m_eImageFileFormat;
	}
	void setEImageFileFormat(ImageFileFormat eImageFileFormat) {
		m_eImageFileFormat = eImageFileFormat;
	}
};


template <class T>
Image<T> operator+(const Image<T>& cIm){
	assert(cIm.m_adImageMatrix && (*cIm.m_adImageMatrix));
	return cIm;
}

template <class T>
Image<T> operator+(T dCte, const Image<T>& cRight){

	Image<T> ret = cRight;

	assert(ret.m_adImageMatrix && (*ret.m_adImageMatrix));

	for(auto y = 0 ; y < ret.m_nHeight ; y++){
		for (auto x = 0; x < ret.m_nWidht; ++x) {
			ret.m_adImageMatrix[y][x] += dCte;
		}
	}
	return (ret);
}

template <class T>
Image<T> operator+(const Image<T>& cImLeft, T dCte){
		return dCte + cImLeft;
}

template <class T>
Image<T> operator+(const Image<T>& cLeft, const Image<T>& cImRight){

	Image<T> ret = cLeft;

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

template <class T>
Image<T> operator-(const Image<T>& cIm){

	Image<T> ret = cIm;

	assert(ret.m_adImageMatrix && (*ret.m_adImageMatrix));
	for(auto y = 0 ; y < ret.m_nHeight ; y++){
		for (auto x = 0; x < ret.m_nWidht; ++x) {
			ret.m_adImageMatrix[y][x] = -ret.m_adImageMatrix[y][x];
		}
	}

	return ret;
}

template <class T>
Image<T> operator-(const Image<T>& cLeft, T dCte){
	Image<T> ret = cLeft;

	assert(ret.m_adImageMatrix && (*ret.m_adImageMatrix));

	for(auto y = 0 ; y < ret.m_nHeight ; y++){
		for (auto x = 0; x < ret.m_nWidht; ++x) {
			ret.m_adImageMatrix[y][x] -= dCte;
		}
	}
	return (ret);
}

template <class T>
Image<T> operator-(T dCte, const Image<T>& cImRight){
	return cImRight - dCte;
}

template <class T>
Image<T> operator-(const Image<T>& cLeft, const Image<T>& cImRight){

	Image<T> ret = cLeft;

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

template <class T>
Image<T> operator*(const Image<T>& cLeft, const Image<T>& cImRight){

	Image<T> ret = cLeft;

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

template <class T>
Image<T> operator*(const Image<T>& cLeft, T dCte){
	Image<T> ret = cLeft;

	assert(ret.m_adImageMatrix && (*ret.m_adImageMatrix));

	for(auto y = 0 ; y < ret.m_nHeight ; y++){
		for (auto x = 0; x < ret.m_nWidht; ++x) {
			ret.m_adImageMatrix[y][x] *= dCte;
		}
	}
	return (ret);
}

template <class T>
Image<T> operator*(T dCte, const Image<T>& cImRight){
	return cImRight + dCte;
}

template <class T>
Image<T> operator/(const Image<T>& cLeft, const Image<T>& cImRight){
	Image<T> ret = cLeft;

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

template <class T>
Image<T> operator/(const Image<T>& cLeft, T dCte){
	Image<T> ret = cLeft;

	assert(ret.m_adImageMatrix && (*ret.m_adImageMatrix));

	for(auto y = 0 ; y < ret.m_nHeight ; y++){
		for (auto x = 0; x < ret.m_nWidht; ++x) {
			ret.m_adImageMatrix[y][x] /= dCte;
		}
	}
	return (ret);
}

template <class T>
Image<T> operator/(T dCte, const Image<T>& cImRight){
	return cImRight + dCte;
}


#endif /* IMAGE_H_ */
