//
// Created by ahmad on 8/15/24.
//

#include "Component.h"

Component::Component(const ComponentArgs& args, const Dimensions& dimensions)
    : _font(args.font), _window(args.window), _args(new ComponentArgs(args)), _dimensions(new Dimensions(dimensions)) {
    _dimensions->size -= dimensions.margin * 2.f;
    _dimensions->position += dimensions.margin;
}

Component::~Component() {
    delete _args;
    delete _dimensions;
}

void Component::onEvent(const sf::Event* event) {}

void Component::onFrame() {}

void Component::setSize(const sf::Vector2f& value) {
    const auto newValue = value - _dimensions->margin * 2.f;

    _dimensions->size = newValue;
}

sf::Vector2f Component::getSize() const {
    return _dimensions->size + _dimensions->margin * 2.f;
}

void Component::setPosition(const sf::Vector2f& value) {
    _dimensions->position += value;
}

sf::Vector2f Component::getPosition() const {
    return _dimensions->position - _dimensions->margin;
}
