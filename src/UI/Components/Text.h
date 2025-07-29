//
// Created by ahmad on 25.12.23.
//

#ifndef TEXT_H
#define TEXT_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Component.h"

class Text : public Component {
public:
    explicit Text(const ComponentArgs& args, const Dimensions& dimensions, std::wstring&& value = L"");

    ~Text() override;

    void onEvent(const sf::Event* event) override;

    [[nodiscard]] std::wstring getString() const;

    [[nodiscard]] sf::Rect<float> getLocalBounds() const;

    void setString(std::wstring& string);

    void setCharacterSize(unsigned int fontSize) const;

    void setStyle(sf::Text::Style style) const;

    void setPadding(sf::Vector2f padding);

    void setBackgroundColor(const sf::Color& color) const;

    void appendString(const std::wstring& string);

    void setSize(const sf::Vector2f& value) override;

    void setPosition(const sf::Vector2f& value) override;

    void clear() const;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
    sf::Text* _sfText;
    sf::Vector2f* _originalSize;
    unsigned int _currentLines;
    sf::RectangleShape* _background;
};


#endif //TEXT_H
