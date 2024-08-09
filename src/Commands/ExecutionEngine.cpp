//
// Created by ahmad on 10.04.24.
//

#include <fstream>
#include <array>
#include <memory>
#include <locale>
#include <vector>
#include <optional>
#include "ExecutionEngine.h"
#include <cstdlib>


ExecutionEngine::ExecutionEngine()
    : _outputStream(nullptr), _currentWorkingDir("~/"),
      _wideConverter(new std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>()) {}

ExecutionEngine::~ExecutionEngine() {
    if (_outputStream) {
        pclose(_outputStream);
    }
    delete _outputStream;
    delete _wideConverter;
}

std::optional<std::wstring> ExecutionEngine::pollCommandOutput() {
    if (!_outputStream) {
        return std::nullopt;
    }

    try {
        constexpr size_t bytesToRead = 1024 * 16;
        std::vector<char> buffer(bytesToRead);
        std::array<char, 8> missingUtfBytesBuffer{};
        char* bufferPointer = buffer.data();
        std::size_t bytesRead;

        bytesRead = fread_unlocked(bufferPointer, sizeof(char), bytesToRead, _outputStream);

        if (bytesRead == 0) {
            return std::nullopt;
        }

        // Check for last character completeness if full buffer read
        auto lastChar = bufferPointer[bytesRead - 1];

        while (!(lastChar == '\n' || lastChar == '\0')) {
            // Last byte may not complete a Unicode symbol, so we need to keep reading until \n or \0
            bytesRead = fread_unlocked(missingUtfBytesBuffer.data(), sizeof(char), 1, _outputStream);

            if (bytesRead == 0) {
                break;
            }

            lastChar = missingUtfBytesBuffer[bytesRead - 1];

            buffer.push_back(lastChar);
        }

        auto str = _wideConverter->from_bytes(buffer.data());

        return std::optional<std::wstring>{str};
    } catch (const std::range_error& e) {
        auto str = _wideConverter->from_bytes(e.what());

        return std::optional<std::wstring>{str};
    }
}

void ExecutionEngine::executeCommand(const std::wstring& command) {
    auto length = command.length();
    char str[length + 1];

    wcstombs(str, command.c_str(), length);

    str[length] = '\0';

    _outputStream = popen(str, "r");
}
