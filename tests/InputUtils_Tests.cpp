//
// Created by ahmad on 31.12.23.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <string>
#include <algorithm>
#include "../src/UI/Utils/InputUtils.h"

using namespace ::testing;

std::wstring generateStr(int len) {
    std::wstring str;

    while (str.size() < len) {
        str += L"word ";
    }

    return str;
}

TEST(InputUtils_getNewLines, No_New_Line) {
    auto totalChars = 100;
    auto expectedLineSize = 20;
    auto wordLength = 5;
    auto charSize = 1;
    auto str = generateStr(totalChars);

    InputUtils::widthBoundedString(str, expectedLineSize, charSize);

    auto actualLineSize = 0;

    for (const auto &c: str) {
        actualLineSize += 1;

        if (c == L'\n') {
            EXPECT_LE(actualLineSize, 20);
            actualLineSize = 0;
        }
    }
}
