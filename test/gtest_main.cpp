/*
 * gtest_main.cpp
 *
 *  Created on: Nov 15, 2017
 *      Author: roni
 */

#include "gtest/gtest.h"
#include "HumanPlayerTest.h"
#include "ComputerPlayerTest.h"

GTEST_API_ int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
