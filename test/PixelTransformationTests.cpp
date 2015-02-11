#include "../core/ImageTransformation/PixelTransformation.h"
#include <boost/filesystem.hpp>
#include <gtest.h>
#include <math.h>

class PixelTransformationTests : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	PixelTransformationTests() {
		// You can do set-up work for each test here.
	}

	virtual ~PixelTransformationTests() {
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


	int sum(int pixel){
		return pixel + 5;
	}

	// Objects declared here can be used by all tests in the test case for Foo.
};

TEST_F(PixelTransformationTests, Operations) {

	Image<int> A_Int(10,10,10);
	//Image<float> A_Float(10,10,10.0f);

	Image<int> negative = PixelTransformation::getInstance().negative(A_Int, 256);
	Image<int> logarithmic = PixelTransformation::getInstance().logarithmic(A_Int, 1);
	Image<int> gamma = PixelTransformation::getInstance().gamma(A_Int, 1, 0.6);

	int C = 5;
	pixelTransformFunction func = [&C](int pixelVal){return pixelVal + C;};
	Image<int> custom = PixelTransformation::getInstance().customTransform(A_Int, func);

	//Assert values
	ASSERT_EQ(sumUp(negative), 24500);
	ASSERT_EQ(sumUp(logarithmic), 10*10*static_cast<int>(1 * log(1 + 10)));
	ASSERT_EQ(sumUp(gamma), 10*10*static_cast<int>(1 * pow(10.0, 0.6)));
	ASSERT_EQ(sumUp(custom), 10*10*(10 + 5));

}

TEST_F(PixelTransformationTests, Visual) {

	Image<int> A("./data/unitTestData/cat.jpg");

	Image<int> negative = PixelTransformation::getInstance().negative(A, 256);
	Image<int> logarithmic = PixelTransformation::getInstance().logarithmic(A, 1);
	Image<int> gamma = PixelTransformation::getInstance().gamma(A, 1, 0.6);

	//negative.save("./data/unitTestData/cat_negative.png");
	//logarithmic.save("./data/unitTestData/cat_log.png");
	//gamma.save("./data/unitTestData/cat_gamma.png");

}
