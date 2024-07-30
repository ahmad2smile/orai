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
    Text::setPosition({_bounds.left, _bounds.top});
    setString(_value);
}

void Text::onEvent(const sf::Event *event) {
    if (event->type == sf::Event::Resized) {
        auto value = Text::getString().toWideString();

        for (int i = 0; i < value.size(); ++i) {
            if (value[i] == L'\n') {
                value.replace(i, 1, L" ");
            }
        }

        setString(value);
    }
}

void Text::setMargin(sf::Vector2f value) {
    _margin = value;

    auto pos = Text::getPosition();

    pos.x += _margin.x;
    pos.y += _margin.y;

    Text::setPosition(pos);
}

sf::Vector2f Text::getPosition() {
    auto value = Transformable::getPosition();

    value.x -= _margin.x;
    value.y -= _margin.y;

    return value;
}

void Text::setPosition(sf::Vector2f value) {
    value.x += _margin.x;
    value.y += _margin.y;

    Transformable::setPosition(value);
}

void Text::setString(std::wstring &value) {
    const unsigned int lineWidth = (unsigned int) _bounds.width * _window.getSize().x;

    InputUtils::widthBoundedString(value, lineWidth, _fontSize);

    _value = value;

    sf::Text::setString(value);
}

//std::string stringToWstring(const std::string &str) {
//    std::string wstr;
//    wstr.reserve(str.length());
//
//    const char *src = str.c_str();
//    wchar_t dst[str.length() + 1];
//    size_t result = mbstowcs(dst, src, str.length() + 1);
//
//    if (result != static_cast<size_t>(-1)) {
//        dst[result] = L'\0'; // Ensure null termination
//
//        return wstr.assign(dst, result); // Use return value to convert wchar_t* to std::string (C++11)
//    } else {
//        throw std::runtime_error("Conversion failed");
//    }
//}

//void Text::setString(std::string &string) {
////    std::string wide = stringToWstring(string);
//
//    onFrame(string);
//}

void Text::appendString(const std::wstring &string) {
    _value.append(string);

    setString(_value);
}

//void Text::appendString(const std::wstring &string) {
//    _value.append(string);
//
//    onFrame(_value);
//}


void Text::clear() {
    _value.clear();

    sf::Text::setString("");
}
