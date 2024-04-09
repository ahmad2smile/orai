//
// Created by ahmad on 25.12.23.
//

#include "Text.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "../Utils/InputUtils.h"

Text::Text(const sf::Font &font, sf::RenderWindow &window) : Text(L"", font, window) {
}

Text::Text(std::wstring &&value, const sf::Font &font, sf::RenderWindow &window) : Text(std::move(value), font,
                                                                                        window,
                                                                                        sf::FloatRect{0, 0, 1.0,
                                                                                                      1.0}) {

}

Text::Text(const std::wstring &&value, const sf::Font &font, sf::RenderWindow &window, sf::FloatRect bounds) :
        _value(value),
        _font(font),
        _bounds(bounds),
        _window(window) {
    Text::setFont(_font);
    Text::setCharacterSize(_fontSize);
    Text::setPosition(_bounds.left, _bounds.top);
    update(_value);
}

void Text::update(std::wstring &value) {
    const unsigned int lineWidth = (unsigned int) _bounds.width * _window.getSize().x;

    InputUtils::widthBoundedString(value, lineWidth, _fontSize);

    _value = value;
    Text::setString(_value);
}

void Text::update(const sf::Event *event) {
    if (event->type == sf::Event::Resized) {
        auto value = Text::getString().toWideString();

        for (int i = 0; i < value.size(); ++i) {
            if (value[i] == L'\n') {
                value.replace(i, 1, L" ");
            }
        }

        update(value);
    }
}
