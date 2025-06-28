//
// Created by ahmad on 10.04.24.
//

#ifndef ORAI_COMMAND_H
#define ORAI_COMMAND_H


#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include "Input.h"
#include "../../Commands/ExecutionEngine.h"
#include "TextList.h"

class Command final : public Component {
public:
    explicit Command(sf::RenderWindow& window, const sf::Font& font, DbContext& dbContext, ExecutionEngine& engine);

    ~Command() override;

    void onEvent(const sf::Event* event) override;

    void onFrame() override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    DbContext& _dbContext;
    ExecutionEngine& _engine;
    Text* _output;
    Input* _input;
    TextList* _suggestions;
    sf::View* _suggestionsView;

    bool _executing;
};


#endif //ORAI_COMMAND_H
