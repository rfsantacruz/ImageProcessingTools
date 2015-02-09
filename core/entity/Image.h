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
//TODO: Make Image a template class to allow at least Image<int> and Image<double>

class Image {
private:

	std::string m_strOriginalPath;
	int m_nWidht;
	int m_nHeight;
	ImageFileFormat m_eImageFileFormat;
	int** m_adImageMatrix;


protected:


public:
	//constructor and destructors
	Image(const std::string& strPath):m_strOriginalPath(strPath){

		cv::Mat cvImage;
		cvImage = cv::imread(strPath ,CV_LOAD_IMAGE_GRAYSCALE);

		m_nHeight = cvImage.rows;
		m_nWidht = cvImage.cols;

		m_eImageFileFormat = EnumUtil::str2ImFFormatEnum(strPath);

		m_adImageMatrix = new int*[m_nHeight];
		for (int x = 0; x < m_nHeight; ++x) {
			m_adImageMatrix[x] = new int[m_nWidht];
			for (int y = 0; y < m_nWidht; ++y) {
				m_adImageMatrix[x][y] = static_cast<int>(cvImage.at<uchar>(x,y));
			}
		}


	}

	Image(int nHeight=100, int nWidth=100, int unValue=0, ImageFileFormat eImgFileFormat=ImageFileFormat::PNG)
	:m_strOriginalPath(""), m_nWidht(nWidth), m_nHeight(nHeight),m_eImageFileFormat(eImgFileFormat){

		m_adImageMatrix = new int*[m_nHeight];
		for (int x = 0; x < m_nHeight; ++x) {
			m_adImageMatrix[x] = new int[m_nWidht];
			for (int y = 0; y < m_nWidht; ++y) {
				m_adImageMatrix[x][y] = unValue;
			}
		}

	}

	//copy constructor
	Image(const Image& src):m_strOriginalPath(src.getStrOriginalPath()), m_nWidht(src.getNWidht()),
			m_nHeight(src.getNHeight()),m_eImageFileFormat(src.getEImageFileFormat()){

		m_adImageMatrix = new int*[m_nHeight];
		for (int x = 0; x < m_nHeight; ++x) {
			m_adImageMatrix[x] = new int[m_nWidht];
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

	//overloading operators
	friend Image operator+(const Image& cIm);
	friend Image operator+(const Image& cLeft, const Image& cRight);
	friend Image operator+(const Image& cLeft, double dCte);
	friend Image operator+(double dCte, const Image& cRight);

	friend Image operator-(const Image& cIm);
	friend Image operator-(const Image& cLeft, const Image& cRight);
	friend Image operator-(const Image& cLeft, double dCte);
	friend Image operator-(double dCte, const Image& cRight);

	friend Image operator*(const Image& cLeft, const Image& cRight);
	friend Image operator*(const Image& cLeft, double dCte);
	friend Image operator*(double dCte, const Image& cRight);

	friend Image operator/(const Image& cLeft, const Image& cRight);
	friend Image operator/(const Image& cLeft, double dCte);
	friend Image operator/(double dCte, const Image& cRight);

	//slice operation
	int& operator()(int nx, int ny);
	int** operator()(int nId, bool bisRow);
	int*** operator()(int nxBegin, int nxEnd, int nyBegin, int nyEnd);


	//functions
	bool save(const std::string& targetPath, ImageFileFormat eFormat=ImageFileFormat::PNG);
	void show(const std::string& windowName="Display Image");
	void print();
	std::map<int,int> histogram();

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

#endif /* IMAGE_H_ */
