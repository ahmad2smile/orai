//
// Created by ahmad on 10.12.23.
//
#include <SFML/Window.hpp>

#include "App.h"

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Components/Input.h"
#include "Components/Text.h"

namespace UI {
    App::App() = default;

    sf::RenderWindow* App::initialize(const int width, const int height, const char* title) {
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

    void App::run(sf::RenderWindow* window) const {
        const auto bgColor = sf::Color(2, 5, 23);
        const auto windowSize = window->getSize();

        sf::View view;

        view.setSize(windowSize.x, windowSize.y); // The view size is the same as the window size
        view.setCenter(400, 300); // The view center is the same as the window center
        view.setViewport(sf::FloatRect(0, 0, 1, 1)); // The view covers the whole window

        const auto initializer = new Text(L"╭─  ╱  ~ ", _font);
        initializer->setStyle(sf::Text::Bold);

        const auto input = new Input(L"", _font);
        input->setFontSize(25);
        input->setMargin(25, 0);

        while (window->isOpen()) {
            sf::Event event{};

            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window->close();
                }

                if (event.type == sf::Event::Resized) {
                    window->setView(
                        sf::View(sf::FloatRect(0, 0, static_cast<float>(event.size.width),
                                               static_cast<float>(event.size.height))));
                }

                initializer->update(&event);
                input->update(&event);
            }

            window->clear(bgColor);

            input->render(window);
            initializer->render(window);

            window->display();
        }
    }
} // UI
