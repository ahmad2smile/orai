//
// Created by ahmad on 30.12.23.
//

#ifndef INPUTUTILS_H
#define INPUTUTILS_H

#include <string>
#include <vector>

struct Line {
    std::string value;
    float offset;
};

class InputUtils {
public:
    static std::vector<Line>* getNewLines(const std::string &input, float line_height);
};


#endif //INPUTUTILS_H
