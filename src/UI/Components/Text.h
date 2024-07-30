//
// Created by ahmad on 25.12.23.
//

#ifndef TEXT_H
#define TEXT_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>


class Text : public sf::Text {
public:
    explicit Text(const sf::Font &font, sf::RenderWindow &window);

    explicit Text(std::wstring &&value, const sf::Font &font, sf::RenderWindow &window);

    explicit Text(const std::wstring &&value, const sf::Font &font, sf::RenderWindow &window, sf::FloatRect bounds);

//    void onFrame(std::wstring &value);

    virtual void onEvent(const sf::Event *event);

    void setMargin(sf::Vector2f value);

    sf::Vector2f getPosition();

    void setPosition(sf::Vector2f value);

    void setString(std::wstring &string);

//    void setString(std::string &string);

    void appendString(const std::wstring &string);

//    void appendString(const std::wstring &string);

    void clear();

protected:
    std::wstring _value;
    sf::Font _font;
    unsigned int _fontSize = 18;
    sf::FloatRect _bounds;
    sf::RenderWindow &_window;
    sf::Vector2f _margin;
};


#endif //TEXT_H
