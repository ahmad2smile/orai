//
// Created by ahmad on 7/4/2025.
//

#include "View.h"
View::View(const sf::RenderWindow& window, const sf::Vector2f& position, const sf::Vector2f& size)
    : sf::View(), _position(new sf::Vector2f(position)), _size(new sf::Vector2f(size)) {
    const auto windowSize2u = window.getSize();
    const sf::Vector2f windowSize{static_cast<float>(windowSize2u.x), static_cast<float>(windowSize2u.y)};

    sf::View::setViewport(sf::FloatRect({position.x / windowSize.x, position.y / windowSize.y},
                                        {size.x / windowSize.x, size.y / windowSize.y}));
    sf::View::setCenter(position + size / 2.f);
    sf::View::setSize(size);
}
View::~View() {
    delete _position;
    delete _size;
}
void View::setPosition(const sf::Vector2f& value) {
    sf::View::setCenter(value + *_size / 2.f);
}

void View::setSize(const sf::Vector2f& value) {
    sf::View::setCenter(*_position + value / 2.f);
}
