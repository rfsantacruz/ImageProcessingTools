#include "../core/entity/Image.h"
#include <boost/filesystem.hpp>
#include <gtest.h>


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

	int sumUp(Image im){
		int result = 0;
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

	Image A(10, 10, 5, ImageFileFormat::PNG);
	Image B(10, 10, 2, ImageFileFormat::PNG);
	double dSumUp = 0;


	dSumUp = sumUp(+A);
	ASSERT_EQ(dSumUp,(10*10*5));

	dSumUp = sumUp(A + 10.0f);
	ASSERT_EQ(dSumUp,(10*10*(5+10)));

	dSumUp = sumUp(A + B);
	ASSERT_EQ(dSumUp,(10*10*(5+2)));

	dSumUp = sumUp(-A);
	ASSERT_EQ(dSumUp,(10*10*(-5)));

	dSumUp = sumUp(A - 10.0f);
	ASSERT_EQ(dSumUp,(10*10*(-5)));

	dSumUp = sumUp(A - B);
	ASSERT_EQ(dSumUp, 10*10*(5-2));

	dSumUp = sumUp(A * 2.0f);
	ASSERT_EQ(dSumUp,10*10*5*2);

	dSumUp = sumUp(A * B);
	ASSERT_EQ(dSumUp, 10*10*5*2);

	dSumUp = sumUp(A / 5.0f);
	ASSERT_EQ(dSumUp, 10*10);

	dSumUp = sumUp(A / B);
	ASSERT_EQ(dSumUp, 10*10*2);

}

TEST_F(ImageTests, SliceOps) {

	//one pixel
	Image A(10,10,10);
	int x = 2, y = 3;
	A(x,y) = 1;
	ASSERT_NE((A(x,y)),10);
	ASSERT_EQ((A(x,y)),1);

	//row
	Image B(10,10,10);
	int** row = B(2,true);
	for (auto ycol = 0; ycol < B.getNWidht(); ++ycol) {
		(*row[ycol]) = 1;
	}
	ASSERT_EQ(B(2,3),1);
	ASSERT_EQ(B(2,4),1);
	ASSERT_EQ(B(2,8),1);

	//col
	Image C(10,10,10);
	int** col = C(2,false);
	for (auto xrow = 0; xrow < B.getNHeight(); ++xrow) {
		(*col[xrow]) = 1;
	}
	ASSERT_EQ(C(1,2),1);
	ASSERT_EQ(C(4,2),1);
	ASSERT_EQ(C(9,2),1);

	//slice
	Image D(10,10,10);
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

	//TODO: Fix image file reading procedure

	boost::filesystem::path sInfilepath("./data/unitTestData/IOImageTestIn.png");
	boost::filesystem::path sOutfilepath("./data/unitTestData/IOImageTestOut.jpg");

	Image A (sInfilepath.string());
	//A.show();
	A.save(sOutfilepath.string(), ImageFileFormat::JPEG);
	ASSERT_TRUE(boost::filesystem::exists(sOutfilepath));

	Image B(sOutfilepath.string());
	for (auto xrow = 0; xrow < A.getNHeight(); ++xrow) {
		for (auto ycol = 0; ycol < B.getNWidht(); ++ycol) {
			ASSERT_EQ(A(xrow,ycol),B(xrow,ycol));
		}
	}
}

TEST_F(ImageTests, HistogramOp) {

	Image A(5,5,10);
	for (auto xrow = 0; xrow < A.getNHeight(); ++xrow) {
		for (auto ycol = 0; ycol < A.getNWidht(); ++ycol) {
			A(xrow,ycol) = xrow;
		}
	}

	std::map<int,int> hist = A.histogram();
	ASSERT_EQ(hist[0], 5);
	ASSERT_EQ(hist[1], 5);
	ASSERT_EQ(hist[2], 5);
	ASSERT_EQ(hist[3], 5);
	ASSERT_EQ(hist[4], 5);

}

TEST_F(ImageTests, ConstructorsAndFields) {

	Image A("./data/unitTestData/IOImageTestIn.png");
	ASSERT_EQ(A.getNHeight(), 159);
	ASSERT_EQ(A.getNWidht(), 317);
	ASSERT_EQ(A.getEImageFileFormat(),ImageFileFormat::PNG);

	Image B(A);
	ASSERT_EQ(A.getNHeight(), B.getNHeight());
	ASSERT_EQ(A.getNWidht(), B.getNWidht());
	ASSERT_EQ(A.getEImageFileFormat(), B.getEImageFileFormat());
	ASSERT_EQ(A.getStrOriginalPath(), B.getStrOriginalPath());
	for (auto xrow = 0; xrow < A.getNHeight(); ++xrow) {
		for (auto ycol = 0; ycol < B.getNWidht(); ++ycol) {
			ASSERT_EQ(A(xrow,ycol),B(xrow,ycol));
		}
	}

	Image C(10,20,10,ImageFileFormat::BMP);
	ASSERT_EQ(C.getNHeight(), 10);
	ASSERT_EQ(C.getNWidht(), 20);
	ASSERT_EQ(sumUp(C),10*20*10);
	ASSERT_EQ(C.getEImageFileFormat(),ImageFileFormat::BMP);

}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
