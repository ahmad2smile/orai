//
// Created by ahmad on 10.04.24.
//

#ifndef ORAI_COMMAND_H
#define ORAI_COMMAND_H


#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include "Input.h"
#include "../../Commands/ExecutionEngine.h"
#include "Scrollable.h"

class Command : public sf::Drawable {
public:
    explicit Command(ExecutionEngine& engine, const sf::Font& font, sf::RenderWindow& window);

    ~Command() override;

    void onEvent(const sf::Event* event);

    void onFrame();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    Input* _input;
    ExecutionEngine& _engine;
    const sf::RenderWindow& _window;
    Scrollable* _scrollable;
    Text* _output;
    const sf::Font& _font;
    bool _executing;
    float _scrollSpeed;

    Text* createOutput(std::wstring&& value) const;
};


#endif//ORAI_COMMAND_H
