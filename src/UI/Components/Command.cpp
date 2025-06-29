//
// Created by ahmad on 10.04.24.
//

#include "Command.h"

#include "Output.h"
#include "TextList.h"
#include <string>

Command::Command(sf::RenderWindow& window, const sf::Font& font, DbContext& dbContext, ExecutionEngine& engine)
    : Component(window, font), _dbContext(dbContext), _engine(engine), _executing(false) {
    const auto windowSize = window.getSize();
    const auto windowHeight = static_cast<float>(windowSize.y);
    const auto windowWidth = static_cast<float>(windowSize.x);

    const auto inputSize = sf::Vector2f(windowWidth, 60);
    const auto inputPosition = sf::Vector2f(0, windowHeight - inputSize.y);

    _input = new Input(window, font, L"", inputPosition, inputSize, {10, 10}, 25);
    _input->setStyle(sf::Text::Bold);

    _output = new Output(window, font, L"", {0, 5}, {windowWidth, windowHeight - inputSize.y}, {10, 10}, 25);
    _output->setStyle(sf::Text::Bold);

    const auto suggestionsSize = sf::Vector2f(windowWidth * 0.75f, windowHeight);
    _suggestions = new TextList(window, font, 25, {0, 0}, suggestionsSize);

    _suggestionsView = new sf::View();
    _suggestionsView->setSize(suggestionsSize);
    _suggestionsView->setCenter(suggestionsSize / 2.f);
    _suggestionsView->setViewport(sf::FloatRect({0.125, 0.125}, {0.75, 0.75}));
}

Command::~Command() {
    delete _input;
    delete _output;
    delete _suggestions;
    delete _suggestionsView;
}

void Command::onFrame() {
    if (_executing) {
        const auto output = _engine.pollCommandOutput();

        if (!output.has_value()) {
            _executing = false;

            return;
        }

        _output->appendString(output.value());
    }
}

void Command::onEvent(const sf::Event* event) {
    _input->onEvent(event);
    _output->onEvent(event);
    _suggestions->onEvent(event);

    const auto windowSize = _window.getSize();
    const auto windowHeight = static_cast<float>(windowSize.y);
    const auto windowWidth = static_cast<float>(windowSize.x);

    const auto commandStr = _input->getString();

    if (event->is<sf::Event::TextEntered>()) {
        if (commandStr.length() > 1) {
            auto items = _dbContext.getSuggestions(commandStr);
            _suggestions->setItems(items);
        } else {
            _suggestions->clear();
        }
    }

    if (!_executing && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) &
                               (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) ||
                                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl))) {

        _input->clear();

        if (commandStr == L"clear") {
            _output->clear();
            return;
        }

        _engine.executeCommand(commandStr);
        _executing = true;

        if (commandStr.size() > 2) {
            _dbContext.addSuggestion(commandStr);
        }
    }

    if (!_executing && event->is<sf::Event::TextEntered>()) {
        const auto inputHeight = _input->getSize().y;

        _input->setPosition({0, windowHeight - inputHeight});
        _input->setSize({windowWidth, inputHeight});

        _output->setSize({windowWidth, windowHeight - inputHeight});
    }

    if (const auto e = event->getIf<sf::Event::Resized>()) {
        const auto inputHeight = _input->getSize().y;
        const auto newHeight = static_cast<float>(e->size.y);
        const auto newWidth = static_cast<float>(e->size.x);

        _input->setPosition({0, newHeight - inputHeight});
        _input->setSize({newWidth, inputHeight});

        _output->setPosition({0, 5});
        _output->setSize({newWidth, newHeight - inputHeight});
    }
}

void Command::draw(sf::RenderTarget& target, const sf::RenderStates states) const {
    target.draw(*_output, states);
    target.draw(*_input, states);
    const auto view = target.getView();

    target.setView(*_suggestionsView);
    target.draw(*_suggestions);
    target.setView(view);
}
