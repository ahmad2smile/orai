//
// Created by ahmad on 25.12.23.
//

#include "Text.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "../Utils/InputUtils.h"

Text::Text(std::wstring&& value, const sf::Font& font, const sf::RenderWindow& window, sf::FloatRect bounds)
    : Text(std::move(value), font, 18, window, bounds) {}

Text::Text(std::wstring&& value, const sf::Font& font, unsigned int fontSize, const sf::RenderWindow& window,
           sf::FloatRect bounds)
    : _text(new sf::Text(value, font, fontSize)), _bounds(bounds), _window(window) {
    _text->setPosition({_bounds.left, _bounds.top});
    setString(value);
}

void Text::onEvent(const sf::Event* event) {
    if (event->type == sf::Event::Resized) {
        auto value = _text->getString().toWideString();

        for (int i = 0; i < value.size(); ++i) {
            if (value[i] == L'\n') {
                value.replace(i, 1, L" ");
            }
        }

        setString(value);
    }
}

sf::Vector2f Text::getPosition() {
    return _text->getPosition();
}

std::wstring Text::getString() {
    return _text->getString();
}

void Text::setSize(sf::Vector2f value) {
    _bounds.height = value.y > 0 ? value.y : _bounds.height;
    _bounds.width = value.x > 0 ? value.x : _bounds.width;
}

void Text::setPosition(sf::Vector2f value) {
    _text->setPosition(value);
}

void Text::setString(std::wstring& value) {
    if (value.length() > 2) {
        float charWidth = _text->findCharacterPos(1).x - _text->findCharacterPos(0).x;

        InputUtils::widthBoundedString(value, _bounds.width, charWidth);
    }

    _text->setString(value);
}

void Text::setCharacterSize(unsigned int fontSize) {
    _text->setCharacterSize(fontSize);
}

void Text::setStyle(sf::Text::Style style) {
    _text->setStyle(style);
}

void Text::appendString(const std::wstring& string) {
    setString(_text->getString().toWideString().append(string));
}

sf::Rect<float> Text::getLocalBounds() {
    auto localBounds = _text->getLocalBounds();

    return localBounds.height > _bounds.height ? _text->getLocalBounds() : _bounds;
}

void Text::clear() {
    _text->setString("");
}

void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*_text);
}
