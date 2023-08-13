//
// Created by ahmad on 8/14/23.
//

#ifndef ORAI_SHELL_H
#define ORAI_SHELL_H

#include <vector>
#include <string>
#include "Statement.h"

namespace Orai {

    class Shell {
    private:
        std::vector<std::string> _previousCommands;
        char buffer[1024];

    public:
        void Run();

        Orai::Statement GetStatement();
    };

} // Orai

#endif //ORAI_SHELL_H
