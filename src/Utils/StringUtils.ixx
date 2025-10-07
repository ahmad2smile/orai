//
// Created by ahmad on 10/7/2025.
//

export module StringUtils;

import <string>;
#ifdef _WIN32
import <windows.h>;
#else
import <cstdlib>;
#endif

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