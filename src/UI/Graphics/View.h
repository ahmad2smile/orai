//
// Created by ahmad on 7/4/2025.
//

#ifndef VIEW_H
#define VIEW_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


class View : public sf::View {
public:
    explicit View(const sf::RenderWindow& window, const sf::Vector2f& position = {0, 0},
                  const sf::Vector2f& size = {18, 18});
    ~View();

    void setPosition(const sf::Vector2f& value);
    void setSize(const sf::Vector2f& value);

private:
    sf::Vector2f* _position;
    sf::Vector2f* _size;
};


#endif //VIEW_H
