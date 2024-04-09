//
// Created by ahmad on 31.12.23.
//

#include "gtest/gtest.h"
#include "../src/UI/Utils/InputUtils.h"

TEST(InputUtils_getNewLines, No_New_Line) {
    EXPECT_EQ(InputUtils::widthBoundedString("Input here", 20)->size(), 1);
}

TEST(InputUtils_getNewLines, New_Lines) {
    const std::string input = "Input here\nNew line 1\nNew line 2\nNew line 3";
    const std::string line0 = "Input here";
    const std::string line1 = "New line 1";
    const std::string line2 = "New line 2";
    const std::string line3 = "New line 3";

    EXPECT_EQ(InputUtils::widthBoundedString(input, 20)->size(), 4);
    EXPECT_EQ(InputUtils::widthBoundedString(input, 20)->at(0).value, line0);
    EXPECT_EQ(InputUtils::widthBoundedString(input, 20)->at(1).value, line1);
    EXPECT_EQ(InputUtils::widthBoundedString(input, 20)->at(2).value, line2);
    EXPECT_EQ(InputUtils::widthBoundedString(input, 20)->at(3).value, line3);
}
