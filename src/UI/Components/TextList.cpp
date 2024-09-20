//
// Created by ahmad on 8/15/24.
//

#include "TextList.h"

#include <iostream>
#include <SFML/Window/Event.hpp>

TextList::TextList(sf::RenderWindow& window, const sf::Font& font, const unsigned int fontSize,
                   const sf::Vector2f& position, const sf::Vector2f& size)
    : Component(window, font, position, size), _items(new std::vector<Text*>()), _fontSize(fontSize), _scrollOffset(0),
      _selectedText(nullptr), _selectedTextIndex(-1) {}

TextList::~TextList() {
    for (const auto item: *_items) {
        delete item;
    }

    _items->clear();
    delete _items;
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
    const auto newText = new Text(_window, _font, std::move(value), newPosition, {size.x, itemHeight}, _fontSize);
    newText->setStyle(sf::Text::Bold);

    _items->push_back(newText);
}
const Text* TextList::getSelectedItem() const {
    return _selectedText;
}

void TextList::clear() const {
    _items->clear();
}

void TextList::onEvent(const sf::Event* event) {
    if (event->type == sf::Event::MouseWheelScrolled) {
        const auto delta = (event->mouseWheelScroll.delta);

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

    if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Tab && !_items->empty()) {
        _selectedTextIndex = (_selectedTextIndex + 1) % _items->size();

        _selectedText = _selectedTextIndex != -1 ? _items->at(_selectedTextIndex) : nullptr;
    }
}

void TextList::draw(sf::RenderTarget& target, const sf::RenderStates states) const {
    const auto listSize = getSize();
    const auto listPos = getPosition();
    auto backgroundToggle = false;


    for (const auto& item: *_items) {
        const auto itemHeight = item->getSize().y;
        const auto itemPos = item->getPosition();

        // Check if the item is within the visible range
        if (itemPos.y + itemHeight > listPos.y && itemPos.y < listPos.y + listSize.y) {
            if (_selectedText == item) {
                item->setBackgroundColor(_colorSelected);
            } else {
                item->setBackgroundColor(backgroundToggle ? _colorDark : _colorLight);
            }

            backgroundToggle = !backgroundToggle;

            target.draw(*item, states);
        }
    }
}
