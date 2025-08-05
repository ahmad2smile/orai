//
// Created by ahmad on 8/15/24.
//

#include "Component.h"

Component::Component(const ComponentArgs& args) : _args(new ComponentArgs(args)) {}

Component::~Component() {
    delete _args;
}

void Component::setSize(const sf::Vector2f& value) {
    _args->size = value;
}

sf::Vector2f Component::getSize() const {
    return _args->size;
}

void Component::setPosition(const sf::Vector2f& value) {
    _args->position = value;
}

sf::Vector2f Component::getPosition() const {
    return _args->position;
}

void Component::onEvent(const sf::Event* event) {}

void Component::onFrame() {}

void Component::draw(sf::RenderTarget& target, sf::RenderStates states) const {}
