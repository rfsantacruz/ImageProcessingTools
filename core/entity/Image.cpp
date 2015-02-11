/*
 * Image.cpp
 *
 *  Created on: Dec 30, 2014
 *      Author: rfsantacruz
 */

#include "Image.h"

//slice operation
template <class T>
T& Image<T>::operator()(int nx, int ny){

	assert(m_adImageMatrix && (*m_adImageMatrix));
	assert(nx >= 0 && nx<m_nHeight && ny >= 0 && ny<m_nWidht);

	return m_adImageMatrix[nx][ny];
}

template <class T>
T** Image<T>::operator()(int nId, bool bisRow){

	assert(m_adImageMatrix && (*m_adImageMatrix));
	T** ret = nullptr;

	if(bisRow){
		assert(nId >= 0 && nId < m_nHeight);
		ret = new T*[m_nWidht];
		for (auto x = 0; x < m_nWidht; ++x)
			ret[x] = &m_adImageMatrix[nId][x];
	}else{
		assert(nId >= 0 && nId < m_nWidht);
		ret = new T*[m_nHeight];
		for (auto y = 0; y < m_nHeight; ++y)
			ret[y] = &m_adImageMatrix[y][nId];
	}

	return ret;
}

template <class T>
T*** Image<T>::operator()(int nxBegin, int nxEnd, int nyBegin, int nyEnd ){

	assert(m_adImageMatrix && (*m_adImageMatrix));

	assert(nxBegin < nxEnd);
	assert(nxBegin >= 0 && nxBegin < m_nHeight);
	assert(nxEnd >= 0 && nxBegin < m_nHeight);

	assert(nyBegin < nyEnd);
	assert(nyBegin >= 0 && nyBegin < m_nWidht);
	assert(nyEnd >= 0 && nyBegin < m_nWidht);

	int nSliceHeight = (nxEnd - nxBegin) + 1;
	int nSliceWidht = (nyEnd - nyBegin) + 1;

	T*** ret = new T**[nSliceHeight];
	for (auto x = 0; x < nSliceHeight; ++x) {
		ret[x] = new T*[nSliceWidht];
		for (auto y = 0; y < nSliceWidht; ++y) {
			ret[x][y] = &m_adImageMatrix[x + nxBegin][y + nyBegin];
		}
	}

	return ret;
}

template <class T>
bool Image<T>::save(const std::string& targetPath, ImageFileFormat eFormat /*=ImageFileFormat::PNG*/){


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

template <class T>
void Image<T>::show(const std::string& windowName /*="Display Image"*/){

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

template <class T>
void Image<T>::print(){
	if(m_adImageMatrix){
		for (auto x = 0; x < m_nHeight; ++x) {
			for (auto y = 0; y < m_nWidht; ++y) {
				std::cout << m_adImageMatrix[x][y]<< '\t';
			}
			std::cout << std::endl;
		}
	}
}

template <class T>
std::map<T,int> Image<T>::histogram(){

	std::map<T,int> grayScaleFreq;

	for (auto y = 0; y < m_nHeight; ++y) {
		for (auto x = 0; x < m_nWidht; ++x) {
			T value = m_adImageMatrix[y][x];
			if(grayScaleFreq.find(value) == grayScaleFreq.end())
				grayScaleFreq[value] =  1;
			else
				grayScaleFreq[value] = grayScaleFreq[value] + 1;
		}
	}

	return grayScaleFreq;
}

//declare possible types
template class Image<uchar>;
template class Image<int>;
template class Image<float>;
template class Image<double>;

