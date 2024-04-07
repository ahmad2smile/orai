//
// Created by ahmad on 21.12.23.
//

#include "Input.h"

#include <SFML/Window/Event.hpp>

#include "../Utils/InputUtils.h"

Input::Input(const std::wstring &&value, const sf::Font &font) : Text(std::move(value), font) {}

void Input::update(const sf::Event *event) {
    if (event->type == sf::Event::TextEntered) {
        const size_t value_size = _value.length();

        // NOTE: Backspace
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
            if (!_value.empty()) {
                _value.erase(value_size - 1);

                Text::update(_value);
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            if (const auto new_index = value_size - 1; new_index > 0) {
                _value.push_back('\n');

                Text::update(_value);
            }
        } else if (event->text.unicode < 128) {
            _value.push_back(static_cast<char>(event->text.unicode));

            Text::update(_value);
        }
    }
}
