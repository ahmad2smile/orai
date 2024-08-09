//
// Created by ahmad on 21.12.23.
//

#include "Input.h"

#include <SFML/Window/Event.hpp>

#include "../Utils/InputUtils.h"

Input::Input(std::wstring&& value, const sf::Font& font, const sf::RenderWindow& window, sf::FloatRect bounds)
    : Text(std::move(value), font, window, bounds) {

    _border = new sf::RectangleShape(sf::Vector2f(bounds.width, bounds.height));
    _border->setFillColor(sf::Color(15, 34, 52, 255));
    _border->setOutlineColor(sf::Color(54, 56, 57));
    _border->setOutlineThickness(2.f);
    _border->setPosition({_bounds.left + 6, _bounds.top});
}

Input::~Input() {
    delete _border;
}

void Input::setSize(sf::Vector2f value) {
    _border->setSize(sf::Vector2f(value.x - 8, value.y - 8));
}

void Input::setPosition(sf::Vector2f value) {
    Text::setPosition({value.x + 8, value.y + 8});

    _border->setPosition({value.x + 6, value.y});
}

void Input::onEvent(const sf::Event* event) {
    Text::onEvent(event);

    if (event->type == sf::Event::TextEntered) {
        auto value = Text::getString();
        const size_t value_size = value.length();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
            if (!value.empty()) {
                value.erase(value_size - 1);

                Text::setString(value);
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            if (const auto new_index = value_size - 1; new_index > 0) {
                value.push_back(L'\n');

                Text::setString(value);
            }
        } else if (event->text.unicode < 128) {
            value.push_back(static_cast<char>(event->text.unicode));

            Text::setString(value);
        }
    }
}

void Input::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*_border);

    Text::draw(target, states);
}
