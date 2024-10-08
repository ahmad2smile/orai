//
// Created by ahmad on 10.04.24.
//

#include "Command.h"
#include "TextList.h"
#include <string>

Command::Command(sf::RenderWindow& window, const sf::Font& font, DbContext& dbContext, ExecutionEngine& engine)
    : Component(window, font), _dbContext(dbContext), _engine(engine), _executing(false), _scrollSpeed(100) {
    const auto windowSize = window.getSize();
    const auto windowHeight = static_cast<float>(windowSize.y);
    const auto windowWidth = static_cast<float>(windowSize.x);

    const auto inputSize = sf::Vector2f(windowWidth - 10, 60);
    const auto inputPosition = sf::Vector2f(10, windowHeight - inputSize.y - 10);

    _input = new Input(window, font, L"", inputPosition, inputSize, 24);
    _input->setStyle(sf::Text::Bold);

    _output = new Text(window, font);
    _output->setCharacterSize(25);
    _output->setStyle(sf::Text::Bold);

    const auto suggestionsSize = sf::Vector2f(windowWidth * 0.75f, windowHeight);
    _suggestions = new TextList(window, font, 25, {0, 0}, suggestionsSize);

    _suggestionsView = new sf::View();
    _suggestionsView->setSize(suggestionsSize);
    _suggestionsView->setCenter(suggestionsSize / 2.f);
    _suggestionsView->setViewport(sf::FloatRect(0.125, 0.125, 0.75, 0.75));
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

        const auto windowSize = _window.getSize();

        _output->appendString(output.value());
        _output->setPosition({_output->getPosition().x, static_cast<float>(windowSize.y) -
                                                                _output->getLocalBounds().height -
                                                                _input->getLocalBounds().height});
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

    if (event->type == sf::Event::TextEntered) {
        if (commandStr.length() > 1) {
            auto items = _dbContext.getSuggestions(commandStr);
            _suggestions->setItems(items);
        } else {
            _suggestions->clear();
        }
    }

    if (!_executing &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) & (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
                                                           sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))) {

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

    if (!_executing && (event->type == sf::Event::TextEntered || event->type == sf::Event::Resized)) {
        const auto inputBounds = _input->getLocalBounds();
        constexpr auto bottomMargin = 10.f;

        _input->setPosition({inputBounds.left, windowHeight - inputBounds.height - bottomMargin});
        _input->setSize(sf::Vector2f(windowWidth - 20, inputBounds.height));
    }

    if (event->type == sf::Event::MouseWheelScrolled) {
        const auto delta = event->mouseWheelScroll.delta * _scrollSpeed;
        auto outputPosition = _output->getPosition();

        _output->setPosition({outputPosition.x, outputPosition.y + delta});

        // Update the view position
        _suggestionsView->setCenter(windowWidth / 2, windowHeight / 2);
    }
}

void Command::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*_output);
    target.draw(*_input);

    target.setView(*_suggestionsView);
    target.draw(*_suggestions);
    target.setView(target.getDefaultView());
}
