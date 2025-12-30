//
// Created by ahmad on 6/20/2025.
//

#ifndef OUTPUT_H
#define OUTPUT_H
#include "Text.h"
#include "src/UI/Graphics/ViewPort.h"

#include <string>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>


class Output final : public Text {
public:
    explicit Output(const ComponentArgs& args, std::wstring&& value, const sf::Vector2f& margin = {10, 10});

    ~Output() override;

    void setSize(const sf::Vector2f& value) override;

    [[nodiscard]] sf::Vector2f getSize() const override;

    void setPosition(const sf::Vector2f& value) override;

    [[nodiscard]] sf::Vector2f getPosition() const override;

    void onEvent(const sf::Event* event) override;

    void appendString(const std::wstring& string) override;

    void scrollToBottom() const;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    float _scrollSpeed;
    ViewPort* _scrollView;
    sf::RectangleShape* _border;
    sf::RectangleShape* _background;
};


#endif //OUTPUT_H
