//
// Created by ahmad on 21.12.23.
//

#include "Input.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <cwctype>

Input::Input(sf::RenderWindow& window, const sf::Font& font, std::wstring&& value, const sf::Vector2f& position,
             const sf::Vector2f& size, const sf::Vector2f& margin, const unsigned int fontSize)
    : Text(window, font, std::move(value), position + margin, size - margin * 2.f, fontSize) {

    _border = new sf::RectangleShape(size - margin * 2.f);
    _border->setFillColor(sf::Color(15, 34, 52, 255));
    _border->setOutlineColor(sf::Color(54, 56, 57));
    _border->setOutlineThickness(2.f);
    _border->setPosition(position + margin);
    _border->setScale({1, 1});
    _border->setOrigin({0, 0});

    _margin = new sf::Vector2f(margin);
}

Input::~Input() {
    delete _border;
    delete _margin;
}

void Input::setSize(const sf::Vector2f& value) {
    const auto newValue = value - *_margin * 2.f;

    Text::setSize(newValue);
    _border->setSize(newValue);
}

sf::Vector2f Input::getSize() const {
    return Text::getSize() + *_margin * 2.f;
}

void Input::setPosition(const sf::Vector2f& value) {
    Text::setPosition(value + *_margin);
    _border->setPosition(value + *_margin);
}

sf::Vector2f Input::getPosition() const {
    return Text::getPosition() - *_margin;
}

void Input::onEvent(const sf::Event* event) {
    Text::onEvent(event);

    if (const auto e = event->getIf<sf::Event::TextEntered>()) {
        auto value = getString();
        const size_t valueSize = value.size();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace)) {
            if (!value.empty()) {
                value.erase(valueSize - 1);

                setString(value);
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) &&
                   !(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) ||
                     sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl))) {
            if (const auto new_index = valueSize - 1; new_index > 0) {
                value.push_back(L'\n');

                setString(value);
            }
            // NOTE: Skip Tab key and Esc
        } else if (e->unicode < 128 && e->unicode != 9 && e->unicode != 27) {
            const auto newChar = static_cast<wchar_t>(e->unicode);

            value.push_back(newChar);
            setString(value);
        }
    }
}

void Input::draw(sf::RenderTarget& target, const sf::RenderStates states) const {
    target.draw(*_border, states);

    Text::draw(target, states);
}
