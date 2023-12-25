// Created by ahmad on 21.12.23.
//

#ifndef INPUT_H
#define INPUT_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class Input {
public:
    explicit Input(const char* value, const sf::Font &font);

    void render(sf::RenderWindow* window) const;

    void update(const char* value);

    void update(const sf::Event* event);

private:
    const char* _value;
    sf::Text _text;
};


#endif //INPUT_H
