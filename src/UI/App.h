//
// Created by ahmad on 10.12.23.
//

#ifndef APP_H
#define APP_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace UI {
    class App {
    public:
        App();

        sf::RenderWindow *initialize(int width, int height, const char *title);

        void run(sf::RenderWindow &window) const;

    private:
        sf::Font _font;
    };
} // UI

#endif // APP_H
