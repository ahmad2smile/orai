// Created by ahmad on 21.12.23.
//

#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Text.h"

class Input : public Text {
public:
    explicit Input(const std::wstring &&value, const sf::Font &font);

    void update(const sf::Event *event) override;
};


#endif //INPUT_H
