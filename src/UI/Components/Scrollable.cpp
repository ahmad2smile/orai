//
// Created by ahmad on 12.01.24.
//

#include "Scrollable.h"

#include <SFML/Window/Event.hpp>

Scrollable::Scrollable(sf::FloatRect bounds, sf::RenderWindow &window) :
        _window(window), _bounds(bounds) {

    const auto windowSize = window.getSize();
    _view = new sf::View({
                                 _bounds.left,
                                 _bounds.top,
                                 _bounds.width * windowSize.x,
                                 _bounds.height * windowSize.y});
    _view->setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));

    _items = new std::vector<sf::Drawable *>();
}

Scrollable::~Scrollable() {
    delete _view;

    for (auto item: *_items) {
        delete item;
    }

    delete _items;
}

void Scrollable::addItem(sf::Drawable *item) const {
    _items->push_back(item);
}

void Scrollable::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.setView(*_view);

    for (const auto &item: *_items) {
        target.draw(*item);
    };

    target.setView(target.getDefaultView());
}

void Scrollable::update(const sf::Event *event) const {
    if (event->type == sf::Event::MouseWheelScrolled) {
        auto scrollAmount = 10.0;

        _view->move(0, event->mouseWheelScroll.delta * scrollAmount);
        _window.setView(*_view);
    }

    // NOTE: Preserve scroll-position when window is resized
    if (event->type == sf::Event::Resized) {
        const auto windowSize = _window.getSize();

        _view->reset({
                             _bounds.left,
                             _bounds.top,
                             _bounds.width * static_cast<float>(windowSize.x),
                             _bounds.height * static_cast<float>(windowSize.y)});
        _window.setView(*_view);
    }

    _window.setView(_window.getDefaultView());
}
