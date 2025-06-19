//
// Created by ahmad on 12.01.24.
//

#include "Scrollable.h"

#include <SFML/Window/Event.hpp>

Scrollable::Scrollable(const sf::Font& font, sf::RenderWindow& window, sf::FloatRect bounds)
    : Scrollable(font, window, bounds, new std::vector<Drawable*>()) {}

Scrollable::Scrollable(const sf::Font& font, sf::RenderWindow& window, sf::FloatRect bounds,
                       std::vector<Drawable*>* items)
    : Component(window, font), _items(items), _bounds(bounds) {

    const auto windowSize = window.getSize();
    _bounds.size.x = _bounds.size.x * windowSize.x;
    _bounds.size.y = _bounds.size.y * windowSize.y;

    _view = new sf::View(_bounds);
    _view->setViewport(_bounds);
}

Scrollable::~Scrollable() {
    delete _view;

    for (auto item: *_items) {
        delete item;
    }

    delete _items;
}

void Scrollable::addItem(Drawable* item) const {
    _items->push_back(item);
}

void Scrollable::onFrame() {
    int prev = -1;
    for (const auto& item: *_items) {
        if (prev != 0) {}
    }
}

void Scrollable::onEvent(const sf::Event* event) {
    if (event->is<sf::Event::MouseWheelScrolled>()) {
        const auto e = event->getIf<sf::Event::MouseWheelScrolled>();
        constexpr auto scrollAmount = 10.0;

        _view->move(sf::Vector2f(0, e->delta * scrollAmount));
        //        _window.setView(*_view);
    }

    // NOTE: Preserve scroll-position when Window is resized
    if (event->is<sf::Event::Resized>()) {
        const auto e = event->getIf<sf::Event::Resized>();
        const auto windowSize = _window.getSize();

        _bounds.size.x = _bounds.size.x * static_cast<float>(windowSize.x);
        _bounds.size.y = _bounds.size.y * static_cast<float>(windowSize.y);

        _view->setViewport(_bounds);
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
