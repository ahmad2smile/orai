// Created by ahmad on 21.12.23.
//

#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Text.h"

class Input : public Text {
public:
    explicit Input(sf::Font &font, sf::RenderWindow &window);

    explicit Input(std::wstring &&value, const sf::Font &font, sf::RenderWindow &window);

    explicit Input(std::wstring &&value, const sf::Font &font, sf::RenderWindow &window, sf::FloatRect bounds);

    void onEvent(const sf::Event *event) override;
};


#endif //INPUT_H
