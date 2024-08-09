//
// Created by ahmad on 10.04.24.
//

#ifndef ORAI_EXECUTIONENGINE_H
#define ORAI_EXECUTIONENGINE_H

#include <string>
#include <sstream>
#include <codecvt>
#include <optional>

class ExecutionEngine {
public:
    ExecutionEngine();
    ~ExecutionEngine();

    void executeCommand(const std::wstring& command);
    std::optional<std::wstring> pollCommandOutput();

private:
    FILE* _outputStream;
    std::string _currentWorkingDir;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>* _wideConverter;
};


#endif //ORAI_EXECUTIONENGINE_H
