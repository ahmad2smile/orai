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
    explicit Input(const ComponentArgs& args, const Dimensions& dimensions, std::wstring&& value);

    ~Input() override;

    void setSize(const sf::Vector2f& value) override;

    [[nodiscard]] sf::Vector2f getSize() const override;

    void setPosition(const sf::Vector2f& value) override;

    [[nodiscard]] sf::Vector2f getPosition() const override;

    void onEvent(const sf::Event* event) override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::RectangleShape* _border;
    sf::Vector2f* _margin;
};

#endif // INPUT_H
