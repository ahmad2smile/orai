//
// Created by ahmad on 12.01.24.
//

#ifndef SCROLLABLE_H
#define SCROLLABLE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Scrollable : public sf::Drawable {
public:
    explicit Scrollable(sf::FloatRect bounds, sf::RenderWindow &window);

    ~Scrollable() override;

    void addItem(sf::Drawable *item) const;

    void update(const sf::Event *event) const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::View *_view;
    std::vector<sf::Drawable *> *_items;
    sf::FloatRect _bounds;
    sf::RenderWindow &_window;
    float _marginX = 0;
    float _marginY = 0;
};


#endif //SCROLLABLE_H
