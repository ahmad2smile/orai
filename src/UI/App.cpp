//
// Created by ahmad on 10.12.23.
//
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "App.h"

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Components/Input.h"
#include "Components/Scrollable.h"
#include "Components/Text.h"

namespace UI {
    App::App() = default;

    sf::RenderWindow *App::initialize(const int width, const int height, const char *title) {
        const auto window = new sf::RenderWindow(sf::VideoMode(width, height), title);

        // NOTE: To avoid screen tearning
        window->setVerticalSyncEnabled(true);
        window->setFramerateLimit(120);


        if (!_font.loadFromFile("FiraCodeNerdFont-Light.ttf")) {
            // error...
            std::cout << "Error loading font" << std::endl;
        }

        return window;
    }

    void App::run(sf::RenderWindow &window) const {
        Text initializer(L"╭─  ╱  ~ ", _font, window);
        initializer.setCharacterSize(25);
        initializer.setStyle(sf::Text::Bold);

        Input input(L"", _font, window, {0, 50, 1, 1});
        input.setCharacterSize(25);
        input.setStyle(sf::Text::Bold);

        Scrollable scrollable({0, 0, 1.0, 1.0}, window);
        scrollable.addItem(&initializer);
        scrollable.addItem(&input);

        while (window.isOpen()) {
            sf::Event event{};

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::Resized) {
                    window.setView(
                            sf::View(sf::FloatRect(0, 0, static_cast<float>(event.size.width),
                                                   static_cast<float>(event.size.height))));
                }

                initializer.update(&event);
                input.update(&event);
                scrollable.update(&event);

            }

            window.clear(sf::Color(2, 5, 23));

            window.draw(scrollable);

            window.display();
        }
    }
} // UI
