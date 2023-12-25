//
// Created by ahmad on 8/13/23.
//

#include <iostream>
#include "Statement.h"

#include <sstream>

namespace Orai {
    Orai::Statement::Statement(const char* raw) : _raw(raw) {}

    std::vector<std::string> Orai::Statement::AndSeparators = {"&", "and", "and run", "& run", "and run independently",
                                                      "& run independently", "and run parallel", "& run parallel"};
    void Statement::Debug() {
        std::cout << "Statement:: " << _raw << std::endl;
    }

    void Statement::ParseCommands() {
        std::stringstream stream = new std::stringstream(_raw);
        std::string command;
        while (std::getline(stream, command, ';')) {
            _commands.push_back(command);
            if (command.empty()) {
                _commands.pop_back();
                break;
            }
        }
    }

    std::vector<std::string> Statement::GetCommands() {
        return _commands;
    }
} // Orai
