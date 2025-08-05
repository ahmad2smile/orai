//
// Created by ahmad on 8/15/24.
//

#include "TextList.h"

#include <iostream>
#include <SFML/Window/Event.hpp>

TextList::TextList(const ComponentArgs& args)
    : Component(args), _items(new std::vector<Text*>()), _scrollOffset(0), _selectedText(nullptr),
      _selectedTextIndex(-1), _backgrounds(new std::vector<sf::RectangleShape*>()) {}

TextList::~TextList() {
    for (const auto item: *_items) {
        delete item;
    }

    for (const auto b: *_backgrounds) {
        delete b;
    }

    _items->clear();
    _backgrounds->clear();
    delete _items;
    delete _backgrounds;
}

void TextList::setItems(std::vector<std::wstring>& values) const {
    _items->clear();

    for (auto& item: values) {
        addItem(std::move(item));
    }
}

void TextList::addItem(std::wstring&& value) const {
    auto newPosition = getPosition();

    if (!_items->empty()) {
        const auto lastItem = _items->back();
        const auto lastPosition = lastItem->getPosition();
        const auto lastSize = lastItem->getSize();

        newPosition = sf::Vector2f{lastPosition.x, lastPosition.y + lastSize.y};
    }

    auto itemHeight = 60.f;
    const auto size = getSize();
    const auto newText = new Text({_args->window, _args->font, _args->fontSize, newPosition, {size.x, itemHeight}},
                                  std::move(value));

    newText->setStyle(sf::Text::Bold);

    _items->push_back(newText);
    _backgrounds->push_back(new sf::RectangleShape({size.x, itemHeight}));
}
const Text* TextList::getSelectedItem() const {
    return _selectedText;
}

void TextList::clear() const {
    _items->clear();
}

void TextList::onEvent(const sf::Event* event) {
    if (event->is<sf::Event::MouseWheelScrolled>()) {
        const auto e = event->getIf<sf::Event::MouseWheelScrolled>();
        const auto delta = (e->delta);

        float itemHeight = 60;
        const auto position = getPosition();

        if (!_items->empty()) {
            itemHeight = _items->at(0)->getSize().y;
        }

        const auto itemsCount = _items->size();

        _scrollOffset -= delta * itemHeight;

        if (_scrollOffset < 0)
            _scrollOffset = 0;
        if (_scrollOffset > static_cast<float>(itemsCount) * itemHeight - position.y)
            _scrollOffset = static_cast<float>(itemsCount) * itemHeight - position.y;
    }

    const auto e = event->getIf<sf::Event::KeyReleased>();

    if (e && e->code == sf::Keyboard::Key::Tab && !_items->empty()) {
        _selectedTextIndex = (_selectedTextIndex + 1) % _items->size();

        _selectedText = _selectedTextIndex != -1 ? _items->at(_selectedTextIndex) : nullptr;
    }
}

void TextList::draw(sf::RenderTarget& target, const sf::RenderStates states) const {
    const auto listSize = getSize();
    const auto listPos = getPosition();
    auto backgroundToggle = false;


    for (auto i = 0; i < _items->size(); ++i) {
        const auto& item = _items->at(i);
        const auto& background = _backgrounds->at(i);

        const auto itemHeight = item->getSize().y;
        const auto itemPos = item->getPosition();

        // Check if the item is within the visible range
        if (itemPos.y + itemHeight > listPos.y && itemPos.y < listPos.y + listSize.y) {
            if (_selectedText == item) {
                background->setFillColor(_colorSelected);
            } else {
                background->setFillColor(backgroundToggle ? _colorDark : _colorLight);
            }

            backgroundToggle = !backgroundToggle;

            target.draw(*item, states);
        }
    }
}
