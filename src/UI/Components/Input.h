// Created by ahmad on 21.12.23.
//

#ifndef INPUT_H
#define INPUT_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class Input {
public:
    explicit Input(const std::string &value, const sf::Font &font);

    void render(sf::RenderWindow* window) const;

    void update(const std::string &value);

    void update(const sf::Event* event);

private:
    std::string _value;
    sf::Font _font;
    std::vector<sf::Text> _lines;
};


#endif //INPUT_H
