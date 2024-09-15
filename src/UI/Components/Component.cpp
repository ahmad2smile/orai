//
// Created by ahmad on 8/15/24.
//

#include "Component.h"

Component::Component(sf::RenderWindow& window, const sf::Font& font, const sf::Vector2f& position,
                             const sf::Vector2f& size)
    : _font(font), _window(window), _size(new sf::Vector2f{size}), _position(new sf::Vector2f{position}) {}

Component::~Component() {
    delete _size;
    delete _position;
}

void Component::onEvent(const sf::Event* event) {}

void Component::onFrame() {}

void Component::setSize(const sf::Vector2f& value) {
    _size->x = value.x;
    _size->y = value.y;
}

sf::Vector2f Component::getSize() const {
    return *_size;
}

void Component::setPosition(const sf::Vector2f& value) {
    _position->x = value.x;
    _position->y = value.y;
}

sf::Vector2f Component::getPosition() const {
    return *_position;
}
