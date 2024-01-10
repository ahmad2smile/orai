//
// Created by ahmad on 25.12.23.
//

#ifndef TEXT_H
#define TEXT_H
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>


class Text {
public:
    explicit Text(const std::string &value, const sf::Font &font);

    void render(sf::RenderWindow* window) const;

    void update(const std::string &value);

    void update(const sf::Event* event);

    void setFontSize(int fontSize);

private:
    std::string _value;
    sf::Font _font;
    int _fontSize = 18;
    std::vector<sf::Text> _lines;
};


#endif //TEXT_H
