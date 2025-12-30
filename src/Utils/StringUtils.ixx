//
// Created by ahmad on 10/7/2025.
//

module;

#include <string>
#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

export module StringUtils;

export struct  StringUtils {
    static std::wstring charsToWideString(const char* input) {
#ifdef _WIN32
        const int size = MultiByteToWideChar(CP_UTF8, 0, input, -1, nullptr, 0);

        std::wstring output(size, 0);
        MultiByteToWideChar(CP_UTF8, 0, input, -1, &output[0], size);
#else
        setlocale(LC_ALL, "en_US.UTF-8");
        size_t size = mbstowcs(nullptr, input.c_str(), 0) + 1;
        std::wstring output(size, 0);
        mbstowcs(&output[0], input.c_str(), size);
#endif
        return output;
    }

    static std::wstring filterControlChars(const std::wstring& input) {
        std::wstring output;
        output.reserve(input.size());
        
        bool inEscapeSeq = false;
        for (size_t i = 0; i < input.size(); ++i) {
            wchar_t c = input[i];
            
            // Detect start of ANSI escape sequence (ESC[)
            if (c == L'\x1B' && i + 1 < input.size() && input[i + 1] == L'[') {
                inEscapeSeq = true;
                continue;
            }
            
            // Skip until end of ANSI escape sequence (letter character)
            if (inEscapeSeq) {
                if ((c >= L'A' && c <= L'Z') || (c >= L'a' && c <= L'z')) {
                    inEscapeSeq = false;
                }
                continue;
            }
            
            // Allow printable characters, newline, tab, and carriage return
            if (c >= 32 || c == L'\n' || c == L'\t' || c == L'\r') {
                output.push_back(c);
            }
        }
        
        return output;
    }

    static std::string wideCharsToString(const wchar_t* input) {
#ifdef _WIN32
        const int size = WideCharToMultiByte(CP_UTF8, 0, input, -1, nullptr, 0, nullptr, nullptr);

        std::string output(size, 0);
        WideCharToMultiByte(CP_UTF8, 0, input, -1, &output[0], size, nullptr, nullptr);
#else
        size_t size = wcstombs(nullptr, input.c_str(), 0) + 1;
        std::string output(size, 0);
        wcstombs(&output[0], input.c_str(), size);
#endif
        return output;
    }
};