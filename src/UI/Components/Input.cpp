//
// Created by ahmad on 21.12.23.
//

#include "Input.h"

#include <cstring>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

Input::Input(const char* value, const sf::Font &font) {
    _value = value;
    _text = sf::Text(_value, font);
}

void Input::render(sf::RenderWindow* window) const {
    window->draw(_text);
}

void Input::update(const char* value) {
    _value = value;
    _text.setString(_value);
}

void Input::update(const sf::Event* event) {
    if (event->type == sf::Event::TextEntered) {
        const size_t value_size = strlen(_value);

        // NOTE: Backspace
        if (event->text.unicode == 8) {
            if (const auto new_index = value_size - 1; new_index > 0) {
                const auto new_value = new char[new_index];

                strcpy(new_value, _value);

                new_value[value_size - 1] = '\0';

                update(new_value);
            }
        }
        else if (event->text.unicode < 128) {
            // TODO: Optimize by pre-allocating some reasonable buffer
            const auto new_value = new char[value_size + 1];
            strcpy(new_value, _value);
            new_value[value_size] = static_cast<char>(event->text.unicode);
            new_value[value_size + 1] = '\0';

            update(new_value);
        }
    }
}
