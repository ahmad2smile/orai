//
// Created by ahmad on 10.12.23.
//
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

#include "App.h"
#include "Components/Command.h"

namespace UI {
    App::App() = default;

    sf::RenderWindow* App::initialize(const int width, const int height, const char* title) {
        const auto window = new sf::RenderWindow(sf::VideoMode(width, height), title);

        window->setView(sf::View(sf::FloatRect(0, 0, static_cast<float>(width), static_cast<float>(height))));

        // NOTE: To avoid screen tearing
        window->setVerticalSyncEnabled(true);
        window->setFramerateLimit(120);

        if (!_font.loadFromFile("FiraCodeNerdFont-Light.ttf")) {
            // error...
            std::cout << "Error loading font" << std::endl;
        }

        return window;
    }

    void App::run(sf::RenderWindow& window) const {
        DbContext dbContext;
        dbContext.initTables();

        const auto engine = new ExecutionEngine(dbContext);

        Command command(window, _font, dbContext, *engine);

        while (window.isOpen()) {
            sf::Event event{};

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::Resized) {
                    // window.setView(sf::View(sf::FloatRect(0, 0, static_cast<float>(event.size.width),
                    //                                       static_cast<float>(event.size.height))));
                }

                command.onEvent(&event);
            }

            command.onFrame();

            window.clear(sf::Color(2, 5, 23));

            window.draw(command);

            window.display();
        }
    }
} // namespace UI
