//
// Created by ahmad on 30.12.23.
//

#include "InputUtils.h"

auto InputUtils::getNewLines(const std::string &input, const float line_height = 20) -> std::vector<Line>* {
    size_t new_line_pos = 0;
    size_t last_line_pos = 0;
    const auto lines = new std::vector<Line>();

    while (new_line_pos != std::string::npos) {
        new_line_pos = input.find('\n', last_line_pos);

        const auto line_len = new_line_pos != std::string::npos
                                  ? new_line_pos - last_line_pos
                                  : input.size() - last_line_pos;

        const auto value = input.substr(last_line_pos, line_len);

        const float offset = lines->size() * line_height;

        lines->push_back(Line{value, offset});
        last_line_pos = new_line_pos + 1;
    }

    return lines;
}
