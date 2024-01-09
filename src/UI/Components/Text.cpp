//
// Created by ahmad on 25.12.23.
//

#include "Text.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

Text::Text(const std::string &value, const sf::Font &font) {
    _value = value;
    _font = font;

    update(_value);
}

void Text::render(sf::RenderWindow* window) const {
    for (const auto &line: _lines) {
        window->draw(line);
    }
}

void Text::update(const std::string &value) {
    _value = value;
    _lines.clear();

    auto new_line_pos = _value.find('\n', 0);

    while (new_line_pos != std::string::npos) {
        const auto line = sf::Text(_value.substr(0, new_line_pos), _font);

        _lines.push_back(line);
        new_line_pos = _value.find('\n', new_line_pos + 1);
    }
}

void Text::update(const sf::Event* event) {
    if (event->type == sf::Event::Resized) {
        update(_value);
    }
}
