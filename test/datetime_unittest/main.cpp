#include <iostream>
#include <assert.h>
#include <cstring>
#include <exception>
#include <iostream>
#include <gtest/gtest.h>
using namespace std;

int main(int argc, char**argv)
{
	::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
