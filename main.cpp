// Copyright 2024 Jason Ossai

#include <fstream>
#include <iostream>
#include "Sokoban.hpp"

/**
 * @brief Starts a Sokoban game.
 * @param size The size of the argument list.
 * @param arguments The command line arguments. This game requires one argument, which is the
 * filename of the level file to load.
 */
int main(const int size, const char* arguments[]) {
    // Check arguments
    if (size < 2) {
        std::cout << "Too few arguments! Require the filename of the level file." << std::endl;
        return 1;
    }

    // Create a Sokoban game object and load the level file
    const std::string levelFilename{ arguments[1] };
    SB::Sokoban sokoban{ levelFilename };

    // Create a window based on the Sokoban game width and height
    const auto windowWidth{ sokoban.width() * SB::TILE_WIDTH };
    const auto windowHeight{ sokoban.height() * SB::TILE_HEIGHT };
    const auto windowVideoMode{ sf::VideoMode(windowWidth, windowHeight) };
    const auto windowTitle = SB::GAME_NAME + " by " + SB::AUTHOR_NAME;
    sf::RenderWindow window(windowVideoMode, windowTitle);
    window.setFramerateLimit(60);

    // Create a map that binds keyboard keys to directions for the player to move
    // Initializer list syntax
    const std::unordered_map<const sf::Keyboard::Key, SB::Direction> movePlayerKeyMap{
        { sf::Keyboard::Key::W, SB::Direction::Up },
        { sf::Keyboard::Key::A, SB::Direction::Left },
        { sf::Keyboard::Key::S, SB::Direction::Down },
        { sf::Keyboard::Key::D, SB::Direction::Right },
        { sf::Keyboard::Key::Up, SB::Direction::Up },
        { sf::Keyboard::Key::Left, SB::Direction::Left },
        { sf::Keyboard::Key::Down, SB::Direction::Down },
        { sf::Keyboard::Key::Right, SB::Direction::Right }
    };

    // Game loop
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }

            // Listen to keypress event
            if (event.type == sf::Event::KeyPressed) {
                // Move player
                const auto itDirection = movePlayerKeyMap.find(event.key.code);
                if (itDirection != movePlayerKeyMap.end()) {
                    sokoban.movePlayer(itDirection->second);
                }

                // Reset the game
                if (event.key.code == sf::Keyboard::R) {
                    sokoban.reset();
                }

                // Undo a move
                if (event.key.code == sf::Keyboard::U) {
                    sokoban.undo();
                }
            }
        }

        sokoban.update(clock.restart().asMicroseconds());

        if (window.isOpen()) {
            window.clear(sf::Color::White);
            window.draw(sokoban);
            window.display();
        }
    }
}
