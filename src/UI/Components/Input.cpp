//
// Created by ahmad on 21.12.23.
//

#include "Input.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

Input::Input(const ComponentArgs& args, std::wstring&& value, const sf::Vector2f& margin, bool isEditable)
    : Text(args, std::move(value), margin), _isEditable(isEditable), _scrollSpeed(10),
      _border(new sf::RectangleShape(args.size)),
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

Input::~Input() {
    delete _scrollView;
    delete _border;
    delete _background;
};

void Input::setSize(const sf::Vector2f& value) {
    Text::setSize(value);
    _scrollView->setSize(Text::getSize());
    _border->setSize(value - *_margin * 2.f);
    _background->setSize(value - *_margin * 2.f);
}

sf::Vector2f Input::getSize() const {
    return Text::getSize();
}

void Input::setPosition(const sf::Vector2f& value) {
    Text::setPosition(value);
    _scrollView->setPosition(value);
    _border->setPosition(value + *_margin);
    _background->setPosition(value + *_margin);
}

sf::Vector2f Input::getPosition() const {
    return Text::getPosition();
}

void Input::onEvent(const sf::Event* event) {
    Text::onEvent(event);

    const auto e = event->getIf<sf::Event::TextEntered>();

    if (e && _isEditable) {
        auto value = getString();
        const size_t valueSize = value.size();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace)) {
            if (!value.empty()) {
                value.erase(valueSize - 1);

                setString(value);
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) &&
                   !(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) ||
                     sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl))) {
            if (const auto new_index = valueSize - 1; new_index > 0) {
                value.push_back(L'\n');

                setString(value);
            }
            // NOTE: Skip Tab key and Esc
        } else if (e->unicode < 128 && e->unicode != 9 && e->unicode != 27) {
            const auto newChar = static_cast<wchar_t>(e->unicode);

            value.push_back(newChar);
            setString(value);
        }
    }

    if (event->getIf<sf::Event::Resized>()) {
        const auto size = Text::getSize();

        _border->setSize(size);
        _background->setSize(size);
    }

    if (const auto scrollEvent = event->getIf<sf::Event::MouseWheelScrolled>()) {
        const auto delta = scrollEvent->delta * _scrollSpeed;
        auto outputPosition = _sfText->getPosition();
        const auto textBounds = _sfText->getLocalBounds();
        const auto inputUpperPoint = outputPosition;
        const auto inputLowerPoint = outputPosition + textBounds.size;;

        const auto local_bounds = _border->getGlobalBounds();

        // NOTE: Check if text is inside the input area
        if (local_bounds.contains(inputUpperPoint) && local_bounds.contains(inputLowerPoint)) {
            return;
        }

        // NOTE: Check if can't go any further up "upper limit"
        if (local_bounds.contains(inputUpperPoint) && delta > 0) {
            return;
        }

        // NOTE: Check if can't go any further down "lower limit"
        if (local_bounds.contains(inputLowerPoint) && delta < 0) {
            return;
        }

        _sfText->setPosition({outputPosition.x, outputPosition.y + delta});
    }
}

void Input::draw(sf::RenderTarget& target, const sf::RenderStates states) const {
    const auto view = target.getView();

    target.setView(*_scrollView);

    target.draw(*_border, states);
    target.draw(*_background, states);
    Text::draw(target, states);

    target.setView(view);
}