//
// Created by ahmad on 25.12.23.
//

#include "Text.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "../Utils/InputUtils.h"

Text::Text(const ComponentArgs& args, std::wstring&& value, const sf::Vector2f& margin)
    : Component(args), _sfText(new sf::Text(args.font, value, args.fontSize)), _currentLines(1),
      _originalSize(new sf::Vector2f(args.size)), _margin(new sf::Vector2f(margin)) {
    _sfText->setPosition(args.position + margin);

    setString(value);
}

Text::~Text() {
    delete _sfText;
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
    auto size = _args->size;

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

void Text::appendString(const std::wstring& string) {
    setString(_sfText->getString().toWideString().append(string));
}

void Text::setSize(const sf::Vector2f& value) {
    Component::setSize(value);
}

void Text::setPosition(const sf::Vector2f& value) {
    Component::setPosition(value);
    _sfText->setPosition(value + *_margin);
}

sf::Rect<float> Text::getLocalBounds() const {
    auto position = getPosition();
    auto size = getSize();

    return {position, size};
}

void Text::clear() const {
    _sfText->setString("");
}

void Text::draw(sf::RenderTarget& target, const sf::RenderStates states) const {
    Component::draw(target, states);
    target.draw(*_sfText, states);
}
