//
// Created by ahmad on 30.12.23.
//

#ifndef INPUTUTILS_H
#define INPUTUTILS_H

#include <string>
#include <vector>

struct Line {
    std::string value;
    int offset;
};

class InputUtils {
public:
    static std::vector<Line>* getNewLines(const std::string &input);
};


#endif //INPUTUTILS_H
