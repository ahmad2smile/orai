//
// Created by ahmad on 10.12.23.
//
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "App.h"

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Components/Command.h"

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
        auto engine = new ExecutionEngine();

        Command command(*engine, _font, window);

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

                command.onEvent(&event);
            }

            command.onFrame();
            
            window.clear(sf::Color(2, 5, 23));

            window.draw(command);

            window.display();
        }
    }
} // UI
