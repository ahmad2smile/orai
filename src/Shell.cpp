//
// Created by ahmad on 8/14/23.
//

#include <cstdio>
#include <cstring>
#include "Shell.h"

namespace Orai {
    enum ShellCodes {
        SUCCESS = 0, FAILURE = 1, EXIT = 2
    };

    void Shell::Run() {
        do {
            printf("Orai> ");
            // Read line to buffer
            fgets(buffer, 1024, stdin);

            if (std::strcmp(buffer, "exit\n") == 0) {
                break;
            }

            if (std::strcmp(buffer, "print last\n") == 0) {
                if (_previousCommands.empty()) {
                    printf("No previous commands\n");
                } else {
                    printf("%s", _previousCommands.back().c_str());
                }
            }

            _previousCommands.emplace_back(buffer);
        } while (true);
    }

    Orai::Statement Shell::GetStatement() {
        return Orai::Statement(buffer);
    }

} // Orai