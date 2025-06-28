//
// Created by ahmad on 6/20/2025.
//

#ifndef OUTPUT_H
#define OUTPUT_H
#include "Text.h"


#include <string>
#include <SFML/Graphics/Font.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>


class Output final : public Text {
public:
    explicit Output(sf::RenderWindow& window, const sf::Font& font, std::wstring&& value = L"",
                   const sf::Vector2f& position = {0, 0}, const sf::Vector2f& size = {18, 18},
                   const sf::Vector2f& margin = {10, -10}, unsigned int fontSize = 18);

    ~Output() override;

    void setSize(const sf::Vector2f& value) override;

    sf::Vector2f getSize() const override;

    void setPosition(const sf::Vector2f& value) override;

    sf::Vector2f getPosition() const override;

    void onEvent(const sf::Event* event) override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::RectangleShape* _border;
    sf::Vector2f* _margin;
    float _scrollSpeed;
};



#endif //OUTPUT_H
