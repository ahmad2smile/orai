//
// Created by ahmad on 30.12.23.
//

#ifndef INPUTUTILS_H
#define INPUTUTILS_H

#include <string>
#include <vector>

struct Line {
    std::wstring value;
    float offset;
};

class InputUtils {
public:
    static std::vector<Line>* getNewLines(const std::wstring &input, float line_height);
};


#endif //INPUTUTILS_H
