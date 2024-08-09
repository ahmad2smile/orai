//
// Created by ahmad on 10.04.24.
//

#include "Command.h"
#include <array>
#include <string>

Command::Command(ExecutionEngine& engine, const sf::Font& font, sf::RenderWindow& window)
    : _engine(engine), _window(window), _font(font), _executing(false), _scrollSpeed(100) {
    const auto windowSize = window.getSize();

    _scrollable = new Scrollable({0, 0, 1.0, 1.0}, window);

    auto inputHeight = 60.f;

    _input = new Input(L"", font, window,
                       {0, (float) window.getSize().y - inputHeight, (float) windowSize.x, inputHeight});
    _input->setCharacterSize(24);
    _input->setStyle(sf::Text::Bold);

    _output = new Text(L"", _font, _window, sf::FloatRect{0, 0, 1.0, 1.0});
    _output->setCharacterSize(25);
    _output->setStyle(sf::Text::Bold);
}

Command::~Command() {
    delete _input;
    delete _scrollable;
    delete _output;
}

void Command::onFrame() {
    if (_executing) {
        auto output = _engine.pollCommandOutput();

        if (!output.has_value()) {
            _executing = false;

            return;
        }

        const auto windowSize = _window.getSize();

        _output->appendString(output.value());
        _output->setPosition({_output->getPosition().x, ((float) windowSize.y) - _output->getLocalBounds().height -
                                                                _input->getLocalBounds().height});
    }
}

void Command::onEvent(const sf::Event* event) {
    _input->onEvent(event);
    _output->onEvent(event);

    if (!_executing && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) &&
        (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))) {

        auto command = _input->getString();
        _input->clear();

        if (command == L"clear") {
            _output->clear();
            return;
        }

        _engine.executeCommand(command);
        _executing = true;
    }

    if (!_executing && (event->type == sf::Event::TextEntered || event->type == sf::Event::Resized)) {
        const auto inputBounds = _input->getLocalBounds();
        const auto windowSize = _window.getSize();

        _input->setPosition({inputBounds.left, ((float) windowSize.y) - inputBounds.height});
        _input->setSize(sf::Vector2f((float) windowSize.x, inputBounds.height));
    }

    if (event->type == sf::Event::MouseWheelScrolled) {
        auto delta = event->mouseWheelScroll.delta * _scrollSpeed;

        auto outputPosition = _output->getPosition();

        _output->setPosition({outputPosition.x, outputPosition.y + delta});
    }
}

void Command::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*_output);
    target.draw(*_input);
}
