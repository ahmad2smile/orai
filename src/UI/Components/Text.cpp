//
// Created by ahmad on 25.12.23.
//

#include "Text.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "../Utils/InputUtils.h"

Text::Text(const std::wstring &&value, const sf::Font &font) {
    _value = value;
    _font = font;

    update(_value);
}

void Text::render(sf::RenderWindow* window) const {
    for (const auto &line: _lines) {
        window->draw(line);
    }
}

void Text::update(const std::wstring &value) {
    _value = value;
    _lines.clear();

    const auto lines = InputUtils::getNewLines(_value, _fontSize);

    for (const auto &[value, offset]: *lines) {
        auto text = sf::Text(value, _font);
        text.setPosition(0, offset);

        _lines.push_back(text);
    }
}

void Text::update(const sf::Event* event) {
    if (event->type == sf::Event::Resized) {
        update(_value);
    }
}

void Text::setFontSize(const int fontSize) {
    _fontSize = fontSize;
}
