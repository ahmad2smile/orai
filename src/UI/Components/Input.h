// Created by ahmad on 21.12.23.
//

#ifndef INPUT_H
#define INPUT_H

#include "Text.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class Input final : public Text {
public:
    explicit Input(sf::RenderWindow& window, const sf::Font& font, std::wstring&& value = L"",
                   const sf::Vector2f& position = {0, 0}, const sf::Vector2f& size = {18, 18},
                   unsigned int fontSize = 18);

    ~Input() override;

    void setSize(const sf::Vector2f& value) override;

    void setPosition(const sf::Vector2f& value) override;

    void onEvent(const sf::Event* event) override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::RectangleShape* _border;
};

#endif // INPUT_H
