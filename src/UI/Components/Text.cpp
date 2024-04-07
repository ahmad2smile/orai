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

void Text::update(const std::wstring &value) {
    _value = value;
    _lines.clear();

    const auto lines = InputUtils::getNewLines(_value, _fontSize);

    for (const auto &[val, offset]: *lines) {
        auto text = sf::Text(val, _font);
        text.setPosition(0 + _marginX, offset + _marginY);

        _lines.push_back(text);
    }
}

void Text::update(const sf::Event *event) {
    if (event->type == sf::Event::Resized) {
        update(_value);
    }
}

void Text::setFontSize(const int fontSize) {
    _fontSize = fontSize;
}

void Text::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const auto &line: _lines) {
        target.draw(line);
    }
}

void Text::setMargin(const float x, const float y) {
    _marginX = x;
    _marginY = y;
}
