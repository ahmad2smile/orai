//
// Created by ahmad on 30.12.23.
//

#include "InputUtils.h"

void InputUtils::widthBoundedString(std::wstring &value, unsigned int lineWidth, unsigned int charSize) {
    const unsigned int maxCharsPerLine = lineWidth / charSize;
    unsigned int lineLength = 0;
    const auto size = value.size();
    int lastSpaceIndex = 0;

    for (int i = 0; i < size; ++i) {
        const auto c = value[i];
        lineLength += 1;

        if (c == L'\n') {
            lineLength = 0;
        } else if (lineLength >= maxCharsPerLine) {
            value.replace(lastSpaceIndex, 1, L"\n");


            lineLength = 0;
        }

        if (c == L' ') {
            lastSpaceIndex = i;
        }
    }
}
