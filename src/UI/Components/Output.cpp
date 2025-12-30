//
// Created by ahmad on 6/20/2025.
//

#include "Output.h"

#include "src/UI/Graphics/ViewPort.h"

#include <algorithm>
#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>

Output::Output(const ComponentArgs& args, std::wstring&& value, const sf::Vector2f& margin)
    : Text(args, std::move(value), margin), _scrollSpeed(100), _border(new sf::RectangleShape(args.size)),
      _background(new sf::RectangleShape(args.size)) {
    _scrollView = new ViewPort(args.window, args.position + margin, args.size - margin * 2.f);

    _background->setSize(args.size - margin * 2.f);
    _background->setPosition(args.position + margin);
    _background->setFillColor(sf::Color(15, 34, 52, 255));

    _border->setSize(args.size - margin * 2.f);
    _border->setPosition(args.position + margin);
    _border->setFillColor(sf::Color::Transparent);
    _border->setOutlineColor(sf::Color(54, 56, 57));
    _border->setOutlineThickness(2.f);
}

Output::~Output() {
    delete _scrollView;
}

void Output::setSize(const sf::Vector2f& value) {
    Text::setSize(value);
    _scrollView->setSize(value - *_margin * 2.f);
    _border->setSize(value - *_margin * 2.f);
    _background->setSize(value - *_margin * 2.f);
}

sf::Vector2f Output::getSize() const {
    return Text::getSize();
}

void Output::setPosition(const sf::Vector2f& value) {
    Text::setPosition(value);
    _scrollView->setPosition(value + *_margin);
    _border->setPosition(value + *_margin);
    _background->setPosition(value + *_margin);
}

sf::Vector2f Output::getPosition() const {
    return Text::getPosition();
}

void Output::onEvent(const sf::Event* event) {
    Text::onEvent(event);

    if (const auto e = event->getIf<sf::Event::MouseWheelScrolled>()) {
        const auto delta = e->delta * _scrollSpeed;
        const float currentScrollY = _scrollView->getScrollY();
        const float newScrollY = currentScrollY - delta;

        // Calculate max scroll
        const auto textBounds = _sfText->getGlobalBounds();
        const auto textPos = _sfText->getPosition();
        const auto viewHeight = _scrollView->getSize().y;
        const auto viewPos = getPosition() + *_margin;

        const float textBottom = textPos.y + textBounds.size.y;
        const float viewBottom = viewPos.y + viewHeight;
        const float maxScroll = std::max(0.f, textBottom - viewBottom);

        _scrollView->setScrollY(std::clamp(newScrollY, 0.f, maxScroll));
    }

    if (event->getIf<sf::Event::Resized>()) {
        const auto size = Text::getSize();

        _border->setSize(size);
        _background->setSize(size);
    }
}

void Output::appendString(const std::wstring& string) {
    Text::appendString(string);
    scrollToBottom();
}

void Output::scrollToBottom() const {
    const auto textBounds = _sfText->getGlobalBounds();
    const auto textPos = _sfText->getPosition();
    const auto viewHeight = _scrollView->getSize().y;
    const auto viewPos = getPosition() + *_margin;

    // Text bottom position relative to viewport top
    const float textBottom = textPos.y + textBounds.size.y;
    const float viewBottom = viewPos.y + viewHeight;

    // Only scroll if there's overflow
    if (const float overflow = textBottom - viewBottom; overflow > 0) {
        _scrollView->setScrollY(overflow);
    } else {
        _scrollView->setScrollY(0);
    }
}

void Output::draw(sf::RenderTarget& target, const sf::RenderStates states) const {
    // Draw border and background without viewport clipping
    target.draw(*_border, states);
    target.draw(*_background, states);

    // Draw text with viewport clipping so it doesn't overflow
    const auto view = target.getView();
    target.setView(*_scrollView);
    Text::draw(target, states);
    target.setView(view);
}
