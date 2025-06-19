//
// Created by ahmad on 25.12.23.
//

#include "Text.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "../Utils/InputUtils.h"

Text::Text(sf::RenderWindow& window, const sf::Font& font, std::wstring&& value, const sf::Vector2f& position,
           const sf::Vector2f& size, const unsigned int fontSize)
    : Component(window, font, position, size), _text(new sf::Text(font, value, fontSize)),
      _background(new sf::RectangleShape(size)) {
    _background->setFillColor(sf::Color::Transparent);
    setString(value);
}

Text::~Text() {
    delete _text;
    delete _background;
}

void Text::onEvent(const sf::Event* event) {
    if (event->is<sf::Event::Resized>()) {
        auto value = _text->getString().toWideString();

        for (int i = 0; i < value.size(); ++i) {
            if (value[i] == L'\n') {
                value.replace(i, 1, L" ");
            }
        }

        setString(value);
    }
}

std::wstring Text::getString() const {
    return _text->getString();
}

void Text::setString(std::wstring& string) {
    const auto size = getSize();
    unsigned long int lines = 1;

    if (string.length() > 2) {
        const float charWidth = _text->findCharacterPos(1).x - _text->findCharacterPos(0).x;

        lines = InputUtils::widthBoundedString(string, size.x, charWidth);
    }

    _text->setString(string);

    setSize({size.x, size.y * static_cast<float>(lines)});
}

void Text::setCharacterSize(const unsigned int fontSize) const {
    _text->setCharacterSize(fontSize);
}

void Text::setStyle(const sf::Text::Style style) const {
    _text->setStyle(style);
}

void Text::setBackgroundColor(const sf::Color& color) const {
    _background->setFillColor(color);
}

void Text::appendString(const std::wstring& string) {
    setString(_text->getString().toWideString().append(string));
}

sf::Rect<float> Text::getLocalBounds() const {
    auto position = getPosition();
    auto size = getSize();

    return {position, size};
}

void Text::clear() const {
    _text->setString("");
}

void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    const auto position = getPosition();
    const auto size = getSize();
    const auto leftPadding = static_cast<float>(_text->getCharacterSize()) / 2.f;
    // NOTE: available space for padding vertically / 2.5f
    const auto topPadding = (size.y - _text->getGlobalBounds().size.y) / 2.5f;

    _background->setSize(size);
    _background->setPosition(position);
    _text->setPosition({position.x + leftPadding, position.y + topPadding});

    target.draw(*_background);
    target.draw(*_text);
}
