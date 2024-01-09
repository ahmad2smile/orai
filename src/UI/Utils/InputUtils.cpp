//
// Created by ahmad on 30.12.23.
//

#include "InputUtils.h"

auto InputUtils::getNewLines(const std::string &input) -> std::vector<Line>* {
    auto new_line_pos = input.find('\n', 0);
    const auto lines = new std::vector<Line>();

    while ((new_line_pos = input.find('\n', new_line_pos + 1)) != std::string::npos) {
        const auto value = input.substr(0, new_line_pos + 1);

        auto line = Line{value, static_cast<int>(lines->size()) * 20};

        lines->push_back(line);
    }

    return lines;
}
