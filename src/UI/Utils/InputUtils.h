//
// Created by ahmad on 30.12.23.
//

#ifndef INPUTUTILS_H
#define INPUTUTILS_H

#include <string>

class InputUtils {
public:
    static void widthBoundedString(std::wstring &value, unsigned int lineWidth, unsigned int charSize);
};


#endif //INPUTUTILS_H
