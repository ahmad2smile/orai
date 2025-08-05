// Created by ahmad on 21.12.23.
//

#ifndef INPUT_H
#define INPUT_H

#include "Text.h"
#include "src/UI/Graphics/ViewPort.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class Input final : public Text {
public:
    explicit Input(const ComponentArgs& args, std::wstring&& value, const sf::Vector2f& margin = {10, 10},
                   bool isEditable = true);

    ~Input() override;

    void setSize(const sf::Vector2f& value) override;

    [[nodiscard]] sf::Vector2f getSize() const override;

    void setPosition(const sf::Vector2f& value) override;

    [[nodiscard]] sf::Vector2f getPosition() const override;

    void onEvent(const sf::Event* event) override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    bool _isEditable;
    float _scrollSpeed;
    ViewPort* _scrollView;
    sf::RectangleShape* _border;
    sf::RectangleShape* _background;
};

#endif // INPUT_H