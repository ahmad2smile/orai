//
// Created by ahmad on 25.12.23.
//

#include "Text.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "../Utils/InputUtils.h"

Text::Text(sf::RenderWindow& window, const sf::Font& font, std::wstring&& value, const sf::Vector2f& position,
           const sf::Vector2f& size, const unsigned int fontSize)
    : Component(window, font, position, size), _sfText(new sf::Text(font, value, fontSize)),
      _originalSize(new sf::Vector2f(size)), _currentLines(1), _background(new sf::RectangleShape(size)) {
    _sfText->setPosition(position);
    _background->setSize(size);
    _background->setPosition(position);
    _background->setFillColor(sf::Color::Transparent);
    setString(value);
}

Text::~Text() {
    delete _sfText;
    delete _background;
    delete _originalSize;
}

void Text::onEvent(const sf::Event* event) {
    if (event->is<sf::Event::Resized>()) {
        auto value = _sfText->getString().toWideString();

        for (int i = 0; i < value.size(); ++i) {
            if (value[i] == L'\n') {
                value.replace(i, 1, L" ");
            }
        }

        setString(value);
    }
}

std::wstring Text::getString() const {
    return _sfText->getString();
}

void Text::setString(std::wstring& string) {
    auto size = Component::getSize();

    if (string.length() > 2) {
        // NOTE: 1.2 add a bit of buffer on new lines on Text as charSize is an approximation for font-width
        const auto character_size = static_cast<float>(_sfText->getCharacterSize()) * 1.2f;

        const auto lines = InputUtils::widthBoundedString(string, size.x, character_size);

        size.y = _originalSize->y + character_size * static_cast<float>(lines);
    }

    _sfText->setString(string);

    Component::setSize(size);
}

void Text::setCharacterSize(const unsigned int fontSize) const {
    _sfText->setCharacterSize(fontSize);
}

void Text::setStyle(const sf::Text::Style style) const {
    _sfText->setStyle(style);
}

void Text::setBackgroundColor(const sf::Color& color) const {
    _background->setFillColor(color);
}

void Text::appendString(const std::wstring& string) {
    setString(_sfText->getString().toWideString().append(string));
}

void Text::setSize(const sf::Vector2f& value) {
    Component::setSize(value);
}

void Text::setPosition(const sf::Vector2f& value) {
    _sfText->setPosition(value);
    Component::setPosition(value);
}

sf::Rect<float> Text::getLocalBounds() const {
    auto position = getPosition();
    auto size = getSize();

    return {position, size};
}

void Text::clear() const {
    _sfText->setString("");
}

void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // const auto position = getPosition();
    // const auto size = getSize();
    // const auto leftPadding = 0 * (static_cast<float>(_text->getCharacterSize()) / 2.f);
    // // NOTE: available space for padding vertically / 2.5f
    // const auto topPadding = 0 * ((size.y - _text->getGlobalBounds().size.y) / 2.5f);
    //
    // _background->setSize(size);
    // _background->setPosition(position);

    target.draw(*_background, states);
    target.draw(*_sfText, states);
}
