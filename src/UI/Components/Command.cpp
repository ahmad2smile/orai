//
// Created by ahmad on 10.04.24.
//

#include <string>
#include <memory>
#include <array>
#include "Command.h"

Command::Command(ExecutionEngine &engine, const sf::Font &font, sf::RenderWindow &window) : _engine(engine),
                                                                                            _window(window),
                                                                                            _font(font),
                                                                                            _executing(false) {
    const auto windowSize = window.getSize();

    _scrollable = new Scrollable({0, 0, 1.0, 1.0}, window);

    _input = new Input(L"", font, window, {0, (float) windowSize.y, 1.0, 1.0});
    _input->setCharacterSize(25);
    _input->setStyle(sf::Text::Bold);
    _input->setMargin({10, -20});
    _output = createOutput(L"");
}

Text *Command::createOutput(std::wstring &&value) const {
    const auto output = new Text(std::move(value), _font, _window);

    output->setCharacterSize(25);
    output->setStyle(Text::Bold);
    output->setMargin({10, -10});

    return output;
}

Command::~Command() {
    delete _input;
    delete _scrollable;
    delete _output;
    delete _outputStream;
}

void Command::onFrame() {
    if (_executing) {
        auto output = _engine.readStream(_outputStream);

        if (!output.has_value()) {
            _engine.closeStream(_outputStream);
            _executing = false;

            return;
        }

        const auto windowSize = _window.getSize();

        _input->clear();

        _output->appendString(output.value());
        _output->setPosition({_output->getPosition().x, ((float) windowSize.y) - _output->getLocalBounds().height});
    }
}

void Command::onEvent(const sf::Event *event) {
    if (!_executing &&
        (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

        auto command = _input->getString().toAnsiString();
        _outputStream = _engine.getStream(command.c_str());
        _executing = true;
    }

    if (!_executing && event->type == sf::Event::TextEntered) {
        _input->onEvent(event);

        const auto inputBounds = _input->getLocalBounds();
        const auto windowSize = _window.getSize();

        _input->setPosition({inputBounds.left, ((float) windowSize.y) - inputBounds.height});
    }
}

void Command::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*_input);
    target.draw(*_output);
}
