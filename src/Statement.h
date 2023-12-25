//
// Created by ahmad on 8/13/23.
//

#ifndef ORAI_STATEMENT_H
#define ORAI_STATEMENT_H

#include <string>
#include <vector>

namespace Orai {

    class Statement {
    private:
        const char *_raw;
        std::vector<std::string> _commands;
        static std::vector<std::string> AndSeparators;

    public:
        explicit Statement(const char *raw);

        void Debug();

        void ParseCommands();

        std::vector<std::string> GetCommands();

    };

} // Orai

#endif //ORAI_STATEMENT_H
