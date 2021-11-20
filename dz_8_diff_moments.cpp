#include "pch.h"
#include <iostream>
#include <vector>
#include <gtest/gtest.h>

using namespace std;
template <typename T>
T min_el(vector<T> v) {
	return *min_element(begin(v), end(v));
}
template <typename T>
T max_el(vector<T> v) {
	return *max_element(begin(v), end(v));
}
TEST(minimum, min_el) {
	vector<int> v1{ 4,2,7,3,-5,0,-3,1 };
	ASSERT_EQ(-6, min_el(v1));
	vector<double> v2{ 4.21, 0.42, 0.4242, 3.13 };
	ASSERT_NEAR(0.42, min_el(v2), 1E-5);
}
TEST(maximum, max_el) {
	vector<int> v1{ 4,2,7,3,-5,0,-3,1 };
	ASSERT_TRUE(7 == max_el(v1));
	vector<double> v2{ 4.21, 0.42, 0.4242, 3.13 };
	ASSERT_DOUBLE_EQ(max_el(v2), 4.21);
}


int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}