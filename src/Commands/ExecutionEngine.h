//
// Created by ahmad on 10.04.24.
//

#ifndef ORAI_EXECUTIONENGINE_H
#define ORAI_EXECUTIONENGINE_H

#include <string>
#include <sstream>
#include <codecvt>
#include <optional>
#include "src/Persistance/DbContext.h"

class ExecutionEngine {
public:
    explicit ExecutionEngine(const DbContext& dbContext);
    ~ExecutionEngine();

    void executeCommand(const std::wstring& command);
    [[nodiscard]] std::optional<std::wstring> pollCommandOutput() const;

private:
    FILE* _outputStream;
    const DbContext& _dbContext;
    std::string _currentWorkingDir;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>* _wideConverter;
};


#endif //ORAI_EXECUTIONENGINE_H
