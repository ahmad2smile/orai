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

    struct ComponentArgs {
        sf::RenderWindow& window;
        const sf::Font& font;
        unsigned int fontSize = 24;
    };

    struct Dimensions {
        sf::Vector2f position = {0, 0};
        sf::Vector2f size = {0, 0};
        sf::Vector2f margin = {0, 0};
    };

protected:
    explicit Component(const ComponentArgs& args, const Dimensions& dimensions);

    ~Component() override;

    virtual void onEvent(const sf::Event* event);

    virtual void onFrame();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

    const sf::Font& _font;
    sf::RenderWindow& _window;
    ComponentArgs* _args;

private:
    Dimensions* _dimensions;
};


#endif //ORAI_COMPONENTBASE_H
