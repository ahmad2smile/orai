//
// Created by ahmad on 10.04.24.
//

#ifndef ORAI_EXECUTIONENGINE_H
#define ORAI_EXECUTIONENGINE_H


#include <string>
#include <sstream>
#include <optional>

class ExecutionEngine {
public:
    FILE* getStream(const char *command);
    std::optional<std::wstring> readStream(FILE* commandStream);
    void closeStream(FILE* commandStream);
    
private:
    
};


#endif //ORAI_EXECUTIONENGINE_H
