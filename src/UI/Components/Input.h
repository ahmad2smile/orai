// Created by ahmad on 21.12.23.
//

#ifndef INPUT_H
#define INPUT_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class Input {
public:
    explicit Input(const std::wstring &value, const sf::Font &font);

    void render(sf::RenderWindow* window) const;

    void update(const std::wstring &value);

    void update(const sf::Event* event);

    void setFontSize(int fontSize);

    void setMargin(float x, float y);

private:
    std::wstring _value;
    sf::Font _font;
    float _fontSize = 18;
    float _marginX = 0;
    float _marginY = 0;
    std::vector<sf::Text> _lines;
};


#endif //INPUT_H
