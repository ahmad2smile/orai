// Created by ahmad on 21.12.23.
//

#ifndef INPUT_H
#define INPUT_H

#include "Text.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class Input : public Text {
public:
    explicit Input(std::wstring&& value, const sf::Font& font, const sf::RenderWindow& window, sf::FloatRect bounds);

    ~Input() override;

    void setSize(sf::Vector2f value) override;

    void setPosition(sf::Vector2f value) override;

    void onEvent(const sf::Event* event) override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::RectangleShape* _border;
};

#endif // INPUT_H
