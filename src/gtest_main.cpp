/*
 * gtest_main.cpp
 *
 *  Created on: Nov 21, 2017
 *      Author: yael
 */

#include "gtest/gtest.h"

GTEST_API_ int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}


