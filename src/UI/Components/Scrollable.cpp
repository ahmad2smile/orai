//
// Created by ahmad on 12.01.24.
//

#include "Scrollable.h"

#include <SFML/Window/Event.hpp>

Scrollable::Scrollable(const sf::Font& font, sf::RenderWindow& window, sf::FloatRect bounds)
    : Scrollable(font, window, bounds, new std::vector<sf::Drawable*>()) {}

Scrollable::Scrollable(const sf::Font& font, sf::RenderWindow& window, sf::FloatRect bounds,
                       std::vector<sf::Drawable*>* items)
    : Component(window, font), _items(items), _bounds(bounds) {

    const auto windowSize = window.getSize();

    _view = new sf::View({_bounds.left, _bounds.top, _bounds.width * windowSize.x, _bounds.height * windowSize.y});
    _view->setViewport(_bounds);
}

Scrollable::~Scrollable() {
    delete _view;

    for (auto item: *_items) {
        delete item;
    }

    delete _items;
}

void Scrollable::addItem(sf::Drawable* item) const {
    _items->push_back(item);
}

void Scrollable::onFrame() {
    int prev = -1;
    for (const auto& item: *_items){
        if (prev != 0){
        } 
    }
}

void Scrollable::onEvent(const sf::Event* event) {
    if (event->type == sf::Event::MouseWheelScrolled) {
        auto scrollAmount = 10.0;

        _view->move(0, event->mouseWheelScroll.delta * scrollAmount);
//        _window.setView(*_view);
    }

    // NOTE: Preserve scroll-position when window is resized
    if (event->type == sf::Event::Resized) {
        const auto windowSize = _window.getSize();

        _view->reset({_bounds.left, _bounds.top, _bounds.width * static_cast<float>(windowSize.x),
                      _bounds.height * static_cast<float>(windowSize.y)});
//        _window.setView(*_view);
    }

//    _window.setView(_window.getDefaultView());
}

void Scrollable::draw(sf::RenderTarget& target, sf::RenderStates states) const {
//    _window.setView(*_view);

    for (const auto& item: *_items) {
        target.draw(*item);
    };

//    _window.setView(_window.getDefaultView());
}
