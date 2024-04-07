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
    explicit Text(const std::wstring &&value, const sf::Font &font);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void update(const std::wstring &value);

    virtual void update(const sf::Event *event);

    void setFontSize(int fontSize);

    void setMargin(float x, float y);

protected:
    float _marginX = 0;
    float _marginY = 0;
    std::wstring _value;
    sf::Font _font;
    float _fontSize = 18;
    std::vector<sf::Text> _lines;
};


#endif //TEXT_H
