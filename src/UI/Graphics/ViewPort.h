//
// Created by ahmad on 7/4/2025.
//

#ifndef VIEW_PORT_H
#define VIEW_PORT_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


class ViewPort : public sf::View {
public:
    explicit ViewPort(const sf::RenderWindow& window, const sf::Vector2f& position = {0, 0},
                      const sf::Vector2f& size = {18, 18});
    ~ViewPort();

    void setPosition(const sf::Vector2f& value);
    void setSize(const sf::Vector2f& value);
    void setScrollY(float scrollY);
    [[nodiscard]] float getScrollY() const { return _scrollY; }

private:
    void updateCenter();
    
    const sf::RenderWindow& _window;
    sf::Vector2f* _position;
    sf::Vector2f* _size;
    float _scrollY = 0.f;
};


#endif //VIEW_PORT_H
