//
// Created by ahmad on 10.04.24.
//

#include <fstream>
#include <array>
#include <memory>
#include <locale>
#include <codecvt>
#include <vector>
#include <optional>
#include "ExecutionEngine.h"

std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;

FILE *ExecutionEngine::getStream(const char *command) {
//    std::unique_ptr<FILE, void (*)(FILE *)> commandStream(popen(command, "r"), [](FILE *pipe) { pclose(pipe); });
    FILE *commandStream = popen(command, "r");

    if (!commandStream) {
        return nullptr;
//        return L"pipe error";
    }

    return commandStream;


//    return result;
}

std::optional<std::wstring> ExecutionEngine::readStream(FILE *commandStream) {
    if (!commandStream) {
        return std::nullopt;
    }

    try {
        constexpr size_t bytesToRead = 1024 * 8;
        std::vector<char> buffer(bytesToRead);
        std::array<char, 8> missingUtfBytesBuffer{};
        char *bufferPointer = buffer.data();
        std::size_t bytesRead;

        bytesRead = fread_unlocked(bufferPointer, sizeof(char), bytesToRead, commandStream);

        if (bytesRead == 0) {
            return std::nullopt;
        }

        // Check for last character completeness if full buffer read
        auto lastChar = bufferPointer[bytesRead - 1];

        while (!(lastChar == '\n' || lastChar == '\0')) {
            // Last byte may not complete a Unicode symbol, so we need to keep reading until \n or \0
            bytesRead = fread_unlocked(missingUtfBytesBuffer.data(), sizeof(char), 1, commandStream);

            if (bytesRead == 0) {
                break;
            }

            lastChar = missingUtfBytesBuffer[bytesRead - 1];

            buffer.push_back(lastChar);
        }

        auto str = conv.from_bytes(buffer.data());

        return std::optional<std::wstring>{str};
    } catch (const std::range_error &e) {
        auto str = conv.from_bytes(e.what());

        return std::optional<std::wstring>{str};
    }
}

void ExecutionEngine::closeStream(FILE *commandStream) {
    if (commandStream) {
        pclose(commandStream);
    }
}
