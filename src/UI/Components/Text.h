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

    void update(std::wstring &value);

    virtual void update(const sf::Event *event);

protected:
    std::wstring _value;
    sf::Font _font;
    unsigned int _fontSize = 18;
    std::vector<sf::Text> _lines;
    sf::FloatRect _bounds;
    sf::RenderWindow &_window;
};


#endif //TEXT_H
