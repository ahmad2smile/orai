//
// Created by ahmad on 30.12.23.
//

#include "InputUtils.h"

unsigned long int InputUtils::widthBoundedString(std::wstring &value, const float lineWidth, const float charSize) {
    const float maxCharsPerLine = lineWidth / charSize;
    float lineLength = 0;
    const auto size = value.size();
    int lastSpaceIndex = 0;
    size_t lines = 1;

    for (int i = 0; i < size; ++i) {
        const auto c = value[i];
        lineLength += 1;

        if (c == L'\n') {
            lineLength = 0;
            lines++;
        } else if (lineLength >= maxCharsPerLine) {
            value.replace(lastSpaceIndex, 1, L"\n");


            lineLength = 0;
            lines++;
        }

        if (c == L' ') {
            lastSpaceIndex = i;
        }
    }

    return lines;
}
