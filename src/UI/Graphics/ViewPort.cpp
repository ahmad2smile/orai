//
// Created by ahmad on 7/4/2025.
//

#include "ViewPort.h"

ViewPort::ViewPort(const sf::RenderWindow& window, const sf::Vector2f& position, const sf::Vector2f& size)
    : View(), _window(window), _position(new sf::Vector2f(position)), _size(new sf::Vector2f(size)), _scrollY(0.f) {
    const auto windowSize2u = window.getSize();
    const sf::Vector2f windowSize{static_cast<float>(windowSize2u.x), static_cast<float>(windowSize2u.y)};

    setViewport(sf::FloatRect({position.x / windowSize.x, position.y / windowSize.y},
                              {size.x / windowSize.x, size.y / windowSize.y}));
    updateCenter();
    View::setSize(size);
}

ViewPort::~ViewPort() {
    delete _position;
    delete _size;
}

void ViewPort::updateCenter() {
    setCenter({_position->x + _size->x / 2.f, _position->y + _size->y / 2.f + _scrollY});
}

void ViewPort::setScrollY(float scrollY) {
    _scrollY = scrollY;
    updateCenter();
}

void ViewPort::setPosition(const sf::Vector2f& value) {
    *_position = value;

    const auto windowSize2u = _window.getSize();
    const sf::Vector2f windowSize{static_cast<float>(windowSize2u.x), static_cast<float>(windowSize2u.y)};
    setViewport(sf::FloatRect({_position->x / windowSize.x, _position->y / windowSize.y},
                              {_size->x / windowSize.x, _size->y / windowSize.y}));
    updateCenter();
    View::setSize(*_size);
}

void ViewPort::setSize(const sf::Vector2f& value) {
    *_size = value;

    const auto windowSize2u = _window.getSize();
    const sf::Vector2f windowSize{static_cast<float>(windowSize2u.x), static_cast<float>(windowSize2u.y)};
    setViewport(sf::FloatRect({_position->x / windowSize.x, _position->y / windowSize.y},
                              {_size->x / windowSize.x, _size->y / windowSize.y}));
    updateCenter();
    View::setSize(*_size);
}
