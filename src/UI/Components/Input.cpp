//
// Created by ahmad on 21.12.23.
//

#include "Input.h"

#include <SFML/Window/Event.hpp>

#include "../Utils/InputUtils.h"

Input::Input(sf::RenderWindow& window, const sf::Font& font, std::wstring&& value, const sf::Vector2f& position,
             const sf::Vector2f& size, const unsigned int fontSize)
    : Text(window, font, std::move(value), position, size, fontSize) {
    _border = new sf::RectangleShape(size);
    _border->setFillColor(sf::Color(15, 34, 52, 255));
    _border->setOutlineColor(sf::Color(54, 56, 57));
    _border->setOutlineThickness(2.f);
    _border->setPosition({size.x + 6, size.y});
}

Input::~Input() {
    delete _border;
}

void Input::setSize(const sf::Vector2f& value) {
    Text::setSize(value);
    _border->setSize(value);
}

void Input::setPosition(const sf::Vector2f& value) {
    Text::setPosition(value);
    _border->setPosition(value);
}

void Input::onEvent(const sf::Event* event) {
    Text::onEvent(event);

    if (event->type == sf::Event::TextEntered) {
        auto value = getString();
        const size_t valueSize = value.size();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
            if (!value.empty()) {
                value.erase(valueSize - 1);

                setString(value);
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) &&
                   !(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
                     sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))) {
            if (const auto new_index = valueSize - 1; new_index > 0) {
                value.push_back(L'\n');

                setString(value);
            }
        } else if (event->text.unicode < 128) {
            value.push_back(static_cast<char>(event->text.unicode));

            setString(value);
        }
    }
}

void Input::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*_border);

    Text::draw(target, states);
}
