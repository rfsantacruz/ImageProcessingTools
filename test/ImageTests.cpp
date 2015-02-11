#include "../core/entity/Image.h"
#include <boost/filesystem.hpp>
#include <gtest.h>
#include <cv.h>
#include <highgui.h>

class ImageTests : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	ImageTests() {
		// You can do set-up work for each test here.
	}

	virtual ~ImageTests() {
		// You can do clean-up work that doesn't throw exceptions here.
	}

	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	template <class T>
	T sumUp(Image<T> im){
		T result = 0;
		for (int y = 0; y < im.getNHeight(); ++y) {
			for (int x = 0; x < im.getNWidht(); ++x) {
				result = result + im(y,x);
			}
		}
		return result;
	}

	// Objects declared here can be used by all tests in the test case for Foo.
};

TEST_F(ImageTests, ArithmeticOps) {

	Image<int> A(10, 10, 5, ImageFileFormat::PNG);
	Image<int> B(10, 10, 2, ImageFileFormat::PNG);
	int dSumUp = 0;

	dSumUp = sumUp(+A);
	ASSERT_EQ(dSumUp,(10*10*5));

	dSumUp = sumUp(A + 10);
	ASSERT_EQ(dSumUp,(10*10*(5+10)));

	dSumUp = sumUp(A + B);
	ASSERT_EQ(dSumUp,(10*10*(5+2)));

	dSumUp = sumUp(-A);
	ASSERT_EQ(dSumUp,(10*10*(-5)));

	dSumUp = sumUp(A - 10);
	ASSERT_EQ(dSumUp,(10*10*(-5)));

	dSumUp = sumUp(A - B);
	ASSERT_EQ(dSumUp, 10*10*(5-2));

	dSumUp = sumUp(A * 2);
	ASSERT_EQ(dSumUp,10*10*5*2);

	dSumUp = sumUp(A * B);
	ASSERT_EQ(dSumUp, 10*10*5*2);

	dSumUp = sumUp(A / 5);
	ASSERT_EQ(dSumUp, 10*10);

	dSumUp = sumUp(A / B);
	ASSERT_EQ(dSumUp, 10*10*2);

}

TEST_F(ImageTests, SliceOps) {

	//one pixel
	Image<double> A(10,10.0,10);
	int x = 2, y = 3;
	A(x,y) = 1.0;
	ASSERT_NE((A(x,y)),10.0);
	ASSERT_EQ((A(x,y)),1.0);

	//row
	Image<float> B(10,10,10.0f);
	float** row = B(2,true);
	for (auto ycol = 0; ycol < B.getNWidht(); ++ycol) {
		(*row[ycol]) = 1.0f;
	}
	ASSERT_EQ(B(2,3),1.0f);
	ASSERT_EQ(B(2,4),1.0f);
	ASSERT_EQ(B(2,8),1.0f);

	//col
	Image<uchar> C(10,10,10);
	uchar** col = C(2,false);
	for (auto xrow = 0; xrow < B.getNHeight(); ++xrow) {
		(*col[xrow]) = 1;
	}
	ASSERT_EQ(C(1,2),1);
	ASSERT_EQ(C(4,2),1);
	ASSERT_EQ(C(9,2),1);

	//slice
	Image<int> D(10,10,10);
	int*** S = D(2,3,2,3);
	for (auto xrow = 0; xrow < 2; ++xrow) {
		for (auto ycol = 0; ycol < 2; ++ycol) {
			(*(S[xrow][ycol])) = 1;
		}
	}

	ASSERT_EQ(D(2,2),1);
	ASSERT_EQ(D(2,3),1);
	ASSERT_EQ(D(3,2),1);
	ASSERT_EQ(D(3,3),1);
}

TEST_F(ImageTests, IOOps) {

	boost::filesystem::path sInfilepath("./data/unitTestData/IOImageTestIn.png");
	boost::filesystem::path sOutfilepath("./data/unitTestData/IOImageTestOut.png");

	Image<int> A(sInfilepath.string());
	//A.show(); //uncomment to show
	//A.print(); //uncomment to print its matrix
	A.save(sOutfilepath.string(), ImageFileFormat::PNG);
	ASSERT_TRUE(boost::filesystem::exists(sOutfilepath));

	Image<int> B(sOutfilepath.string());
	for (auto xrow = 0; xrow < A.getNHeight(); ++xrow) {
		for (auto ycol = 0; ycol < B.getNWidht(); ++ycol) {
			ASSERT_EQ(A(xrow,ycol),B(xrow,ycol));
		}
	}
}

TEST_F(ImageTests, HistogramOp) {

	Image<double> A(5,5,10.0);
	for (auto xrow = 0; xrow < A.getNHeight(); ++xrow) {
		for (auto ycol = 0; ycol < A.getNWidht(); ++ycol) {
			A(xrow,ycol) = xrow;
		}
	}

	std::map<double,int> hist = A.histogram();
	ASSERT_EQ(hist[0], 5);
	ASSERT_EQ(hist[1], 5);
	ASSERT_EQ(hist[2], 5);
	ASSERT_EQ(hist[3], 5);
	ASSERT_EQ(hist[4], 5);

}

TEST_F(ImageTests, ConstructorsAndFields) {

	Image<int> A("./data/unitTestData/IOImageTestIn.png");
	ASSERT_EQ(A.getNHeight(), 159);
	ASSERT_EQ(A.getNWidht(), 317);
	ASSERT_EQ(A.getEImageFileFormat(),ImageFileFormat::PNG);

	Image<int> B(A);
	ASSERT_EQ(A.getNHeight(), B.getNHeight());
	ASSERT_EQ(A.getNWidht(), B.getNWidht());
	ASSERT_EQ(A.getEImageFileFormat(), B.getEImageFileFormat());
	ASSERT_EQ(A.getStrOriginalPath(), B.getStrOriginalPath());
	for (auto xrow = 0; xrow < A.getNHeight(); ++xrow) {
		for (auto ycol = 0; ycol < B.getNWidht(); ++ycol) {
			ASSERT_EQ(A(xrow,ycol),B(xrow,ycol));
		}
	}

	Image<int> C(10,20,10,ImageFileFormat::BMP);
	ASSERT_EQ(C.getNHeight(), 10);
	ASSERT_EQ(C.getNWidht(), 20);
	ASSERT_EQ(sumUp(C),10*20*10);
	ASSERT_EQ(C.getEImageFileFormat(),ImageFileFormat::BMP);

}

TEST_F(ImageTests, Other) {
	//debug testes
	/*boost::filesystem::path sInfilepath("./data/unitTestData/IOImageTestIn.png");
	Image A(sInfilepath.string());
	A.print();
	A.show(); //uncomment to show*/
}
