#include "../core/entity/Image.h"
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
				int* pixelVal = im(y,x);
				result = result + (*pixelVal);
			}
		}
		return result;
	}

	// Objects declared here can be used by all tests in the test case for Foo.
};

//TODO Implement unit tests for image class
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

	/*//one pixel
	Image A(10,10,10);
	int x = 2, y = 3;
	A(y,x) = 0;
	ASSERT_NE(*(A(y,x)),10)
	ASSERT_EQ(*(A(y,x)),0);

	//row
	Image B(10,10,10);
	double L[10] = {1};
	B(2,true) = L;
	ASSERT_EQ(B(2,3),1);
	ASSERT_EQ(B(2,4),1);
	ASSERT_EQ(B(2,8),1);

	//col
	Image C(10,10,10);
	double adC[10] = {1};
	C(2,false) = adC;
	ASSERT_EQ(C(1,2),1);
	ASSERT_EQ(C(4,2),1);
	ASSERT_EQ(C(9,2),1);

	//slice
	Image D(10,10,10);
	double S[2][2] = {1};
	D(2,3,2,3) = S;
	ASSERT_EQ(D(2,2),1);
	ASSERT_EQ(D(2,3),1);
	ASSERT_EQ(D(3,2),1);
	ASSERT_EQ(D(3,3),1);
*/}

TEST_F(ImageTests, IOOps) {

	/*Image A ("");
	A.show();
	A.save("", ImageFileFormat::BMP);*/

}

TEST_F(ImageTests, HistogramOp) {

	/*Image A;
	Histogram = A.histogram();
	ASSERT_EQ();*/

}

TEST_F(ImageTests, ConstructorsAndFields) {
	//test constructors and its member access functions
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
