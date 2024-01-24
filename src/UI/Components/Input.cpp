//
// Created by ahmad on 21.12.23.
//

#include "Input.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "../Utils/InputUtils.h"

Input::Input(const std::wstring &value, const sf::Font &font) {
    _value = value;
    _font = font;

    update(_value);
}

void Input::render(sf::RenderWindow* window) const {
    for (const auto &line: _lines) {
        window->draw(line);
    }
}

void Input::update(const std::wstring &value) {
    _value = value;
    _lines.clear();

    const auto lines = InputUtils::getNewLines(_value, _fontSize);

    for (const auto &[value, offset]: *lines) {
        auto text = sf::Text(value, _font);
        text.setPosition(0 + _marginX, offset + _marginY);

        _lines.push_back(text);
    }
}

void Input::update(const sf::Event* event) {
    if (event->type == sf::Event::TextEntered) {
        const size_t value_size = _value.length();

        // NOTE: Backspace
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
            if (!_value.empty()) {
                _value.erase(_value.length() - 1);

                update(_value);
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            if (const auto new_index = value_size - 1; new_index > 0) {
                _value.push_back('\n');

                update(_value);
            }
        }
        else if (event->text.unicode < 128) {
            _value.push_back(static_cast<char>(event->text.unicode));

            update(_value);
        }
    }
}

void Input::setFontSize(const int fontSize) {
    _fontSize = fontSize;
}

void Input::setMargin(const float x, const float y) {
    _marginX = x;
    _marginY = y;
}
