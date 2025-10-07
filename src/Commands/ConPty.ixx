//
// Created by ahmad on 10/5/2025.
//

export module ConPty;

import <windows.h>;

export class ConPty {
    HANDLE _hInputRead = nullptr;
    HANDLE _hInputWrite = nullptr;
    HANDLE _hOutputRead = nullptr;
    HANDLE _hOutputWrite = nullptr;
    HPCON _hPseudoCon = nullptr;
    PROCESS_INFORMATION pi = {nullptr};
    void* threadMemory = nullptr;

public:
    int initialize() {
        CreatePipe(&_hInputRead, &_hInputWrite, nullptr, 0);
        CreatePipe(&_hOutputRead, &_hOutputWrite, nullptr, 0);

        constexpr COORD size = {120, 30};
        if (const auto hr = CreatePseudoConsole(size, _hInputRead, _hOutputWrite, 0, &_hPseudoCon); FAILED(hr))
            return 1;

        STARTUPINFOEX si = {sizeof(STARTUPINFOEX)};
        SIZE_T attrListSize;
        InitializeProcThreadAttributeList(nullptr, 1, 0, &attrListSize);

        threadMemory = calloc(attrListSize, 1);

        si.lpAttributeList = static_cast<LPPROC_THREAD_ATTRIBUTE_LIST>(threadMemory);
        InitializeProcThreadAttributeList(si.lpAttributeList, 1, 0, &attrListSize);
        UpdateProcThreadAttribute(si.lpAttributeList, 0,
                                  PROC_THREAD_ATTRIBUTE_PSEUDOCONSOLE, _hPseudoCon,
                                  sizeof(HPCON), nullptr, nullptr);

        CreateProcess(nullptr, const_cast<LPSTR>("pwsh"), nullptr, nullptr, TRUE,
                      EXTENDED_STARTUPINFO_PRESENT, nullptr, nullptr, &si.StartupInfo, &pi);

        return 0;
    }

    [[nodiscard]] bool readFromConsole(char* buffer, const unsigned long bufferSize, unsigned long* bytesRead) const { // NOLINT(*-convert-member-functions-to-static)
        BOOL result = false;
        DWORD inBytesRead;

        if (PeekNamedPipe(_hOutputRead, nullptr, 0, nullptr, &inBytesRead, nullptr) && inBytesRead > 0) {
            result = ReadFile(_hOutputRead, buffer, bufferSize, &inBytesRead, nullptr);
            buffer[inBytesRead] = '\0';
            *bytesRead = inBytesRead;
        }

        return result;
    }

    [[nodiscard]] bool writeToConsole(const char* input, const int inputLength) const { // NOLINT(*-convert-member-functions-to-static)
        DWORD bytesWritten;

        return WriteFile(_hInputWrite, input, inputLength, &bytesWritten, nullptr);
    }

    ~ConPty() {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        ClosePseudoConsole(_hPseudoCon);
        CloseHandle(_hInputRead);
        CloseHandle(_hInputWrite);
        CloseHandle(_hOutputRead);
        CloseHandle(_hOutputWrite);
        free(threadMemory);
    }

};