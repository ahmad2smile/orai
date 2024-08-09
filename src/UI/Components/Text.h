//
// Created by ahmad on 25.12.23.
//

#ifndef TEXT_H
#define TEXT_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>


class Text : public sf::Drawable {
public:
    explicit Text(std::wstring&& value, const sf::Font& font, const sf::RenderWindow& window, sf::FloatRect bounds);

    explicit Text(std::wstring&& value, const sf::Font& font, unsigned int fontSize, const sf::RenderWindow& window, sf::FloatRect bounds);

    virtual void onEvent(const sf::Event* event);

    sf::Vector2f getPosition();

    std::wstring getString();
    
    sf::Rect<float> getLocalBounds();

    virtual void setSize(sf::Vector2f value);

    virtual void setPosition(sf::Vector2f value);

    void setString(std::wstring& string);
    
    void setCharacterSize(unsigned int fontSize);

    void setStyle(sf::Text::Style style);

    void appendString(const std::wstring& string);
    
    void clear();
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

protected:
    sf::Text* _text;
    sf::FloatRect _bounds;
    const sf::RenderWindow& _window;
};


#endif //TEXT_H
