//
// Created by ahmad on 12.01.24.
//

#ifndef SCROLLABLE_H
#define SCROLLABLE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Component.h"

class Scrollable : public Component {
public:
    explicit Scrollable(const sf::Font& font, sf::RenderWindow& window, sf::FloatRect bounds);
    explicit Scrollable(const sf::Font& font, sf::RenderWindow& window, sf::FloatRect bounds, std::vector<sf::Drawable*>* items);

    ~Scrollable() override;

    void addItem(sf::Drawable* item) const;
    
    void onFrame() override;

    void onEvent(const sf::Event *event) override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::View* _view;
    std::vector<sf::Drawable*>* _items;
    sf::FloatRect _bounds;
};


#endif //SCROLLABLE_H
