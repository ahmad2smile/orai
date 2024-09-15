//
// Created by ahmad on 8/15/24.
//

#ifndef ORAI_COMPONENTBASE_H
#define ORAI_COMPONENTBASE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Component : public sf::Drawable {
public:
    void virtual setSize(const sf::Vector2f& value);
    [[nodiscard]] virtual sf::Vector2f getSize() const;
    void virtual setPosition(const sf::Vector2f& value);
    [[nodiscard]] virtual sf::Vector2f getPosition() const;

protected:
    Component(sf::RenderWindow& window, const sf::Font& font, const sf::Vector2f& position = {0, 0},
                  const sf::Vector2f& size = {0, 0});

    ~Component() override;

    virtual void onEvent(const sf::Event* event);

    virtual void onFrame();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

    const sf::Font& _font;
    sf::RenderWindow& _window;

private:
    sf::Vector2f* _size;
    sf::Vector2f* _position;
};


#endif //ORAI_COMPONENTBASE_H
