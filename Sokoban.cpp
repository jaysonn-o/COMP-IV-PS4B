// Copyright 2024 Jason Ossai

#include "Sokoban.hpp"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <utility>
#include "SokobanConstants.hpp"

namespace SB {

    Sokoban::Sokoban() {
        loadSound(SOUND_BACKGROUND);
        loadSound(SOUND_WIN);

        m_font.loadFromFile(FONT_ROBOTO_FILENAME);
    }

    Sokoban::Sokoban(const std::string& filename) : Sokoban() {
        std::ifstream ifstream{ filename };
        if (!ifstream.is_open()) {
            throw std::invalid_argument("File not found: " + filename);
        }

        ifstream >> *this;
    }

    void Sokoban::movePlayer(const Direction& direction) {
        // If the player has won the game, it can't move anymore
        if (isWon()) {
            return;
        }

        const State state = { m_playerOrientation, m_playerLoc, m_tileCharGrid, m_score };

        // Change the player's orientation
        m_playerOrientation = direction;

        // Find the coordinate of the block to move to
        const auto nextLoc{ getNextLoc(m_playerLoc, direction) };

        // If the next location is out of the map, stay on the spot
        const auto nextLocIndex = getIndex(nextLoc);
        if (nextLoc.x < 0 || nextLoc.x >= m_width || nextLocIndex < 0 ||
            nextLocIndex >= m_width * m_height) {
            return;
        }

        // Get the texture of the next block
        const auto nextBlock = getTileChar(nextLoc);

        // If the coordinate corresponds to a wall block or a box storage, stay on the spot
        if (nextBlock == TileChar::Wall) {
            return;
        }

        // If the coordinate corresponds to an box block, try to push the box to the other side
        if (nextBlock == TileChar::Box || nextBlock == TileChar::BoxStorage) {
            const auto canMoveBox = moveBox(nextLoc, direction);
            if (!canMoveBox) {
                return;
            }
        }

        // Save the current move
        m_stateStack.push(state);

        // Update player location
        m_playerLoc = nextLoc;
    }

    void Sokoban::reset() {
        // Reset m_hasWon and m_stateStack
        m_hasWon = false;
        while (!m_stateStack.empty()) {
            m_stateStack.pop();
        }

        // Perform a shallow copy for the tile char grid
        m_tileCharGrid = m_initialTileCharGrid;

        // Traverse the tile grid
        auto boxCount{ 0 };
        auto storageCount{ 0 };
        auto boxStorageCount{ 0 };
        traverseTileCharGrid([&](auto coordinate, auto tileChar) {
            m_tileGrid.push_back(getTile(tileChar));
            if (tileChar == TileChar::Player) {
                m_playerLoc = coordinate;
                setTileChar(coordinate, TileChar::Empty);
            }
            else if (tileChar == TileChar::Box) {
                ++boxCount;
            }
            else if (tileChar == TileChar::Storage) {
                ++storageCount;
            }
            else if (tileChar == TileChar::BoxStorage) {
                ++boxStorageCount;
            }

            return false;
            });

        // Set the score and max score
        m_score = boxStorageCount;
        m_maxScore = std::min(storageCount, boxCount) + boxStorageCount;

        // Reset the player's orientation
        m_playerOrientation = DEFAULT_ORIENTATION;

        // Reset the time
        m_elapsedTimeInMicroseconds = 0;

        // Reset the background music
        if (m_soundMap.find(SOUND_BACKGROUND) != m_soundMap.end()) {
            m_soundMap.at(SOUND_BACKGROUND).first->play();
        }
    }

    void Sokoban::undo() {
        if (isWon() || m_stateStack.size() == 0) {
            return;
        }

        const auto [playerOrientation, playerLoc, tileCharGrid, score] = m_stateStack.top();
        m_stateStack.pop();

        m_playerOrientation = playerOrientation;
        m_playerLoc = playerLoc;
        m_tileCharGrid = tileCharGrid;

        m_tileGrid.clear();
        traverseTileCharGrid([&](auto coordinate, auto tileChar) {
            m_tileGrid.push_back(getTile(tileChar));
            if (tileChar == TileChar::Player) {
                m_playerLoc = coordinate;
                setTileChar(coordinate, TileChar::Empty);
            }

            return false;
            });

        m_score = score;
    }

    void Sokoban::update(const int64_t& dt) {
        if (!isWon()) {
            // If the player has won, don't update the elapsed time
            SokobanElapsedTime::update(dt);
        }

        // Check if the player wins the game
        if (!m_hasWon && isWon()) {
            m_hasWon = true;

            // Stop the background music
            if (m_soundMap.find(SOUND_BACKGROUND) != m_soundMap.end()) {
                m_soundMap.at(SOUND_BACKGROUND).first->stop();
            }

            // Reset the player's orientation
            m_playerOrientation = DEFAULT_ORIENTATION;

            // Play the win sound effect
            if (m_soundMap.find(SOUND_WIN) != m_soundMap.end()) {
                m_soundMap.at(SOUND_WIN).first->play();
            }
        }
    }

    std::ifstream& operator>>(std::ifstream& ifstream, Sokoban& sokoban) {
        sokoban.m_initialTileCharGrid.clear();

        // The first line consists of height and width; ignore the rest of the line
        ifstream >> sokoban.m_height >> sokoban.m_width;
        ifstream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Continue the read the following lines
        for (int row{ 0 }; row < sokoban.m_height; ++row) {
            std::string line;
            getline(ifstream, line);
            for (int col{ 0 }; col < sokoban.m_width; ++col) {
                sokoban.m_initialTileCharGrid.push_back(static_cast<TileChar>(line.at(col)));
            }
        }

        sokoban.reset();

        return ifstream;
    }

    std::ofstream& operator<<(std::ofstream& ofstream, const Sokoban& sokoban) {
        ofstream << sokoban.height() << sokoban.width();

        const auto player_loc = sokoban.m_playerLoc;
        sokoban.traverseTileCharGrid([&](auto coordinate, auto tileChar) {
            if (coordinate.x == 0) {
                ofstream << std::endl;
            }

            if (coordinate == player_loc) {
                ofstream << static_cast<char>(TileChar::Player);
            }
            else {
                ofstream << static_cast<char>(tileChar);
            }

            return false;
            });

        return ofstream;
    }

    void Sokoban::draw(sf::RenderTarget& target, const sf::RenderStates states) const {
        SokobanTileGrid::draw(target, states);
        SokobanPlayer::draw(target, states);
        SokobanElapsedTime::draw(target, states);
        SokobanScore::draw(target, states);

        // Display the victory notice if the player has won the game
        if (m_hasWon) {
            drawResultScreen(target, states);
        }
    }

    sf::Vector2i Sokoban::getNextLoc(const sf::Vector2i& currentLoc, const Direction& orientation) {
        sf::Vector2i nextLoc(currentLoc);
        switch (orientation) {
        case Direction::Up:
            --nextLoc.y;
            break;
        case Direction::Down:
            ++nextLoc.y;
            break;
        case Direction::Left:
            --nextLoc.x;
            break;
        case Direction::Right:
            ++nextLoc.x;
            break;
        }

        return nextLoc;
    }

    bool Sokoban::moveBox(const sf::Vector2i& fromCoordinate, const Direction& direction) {
        const auto toCoordinate{ getNextLoc(fromCoordinate, direction) };

        // If the destination coordinate is out of the map, return false
        const auto toCoordinateIndex = getIndex(toCoordinate);
        if (toCoordinate.x < 0 || toCoordinate.x >= m_width || toCoordinateIndex < 0 ||
            toCoordinateIndex >= m_width * m_height) {
            return false;
        }

        const auto currentBlock{ getTileChar(fromCoordinate) };
        const auto nextBlock{ getTileChar(toCoordinate) };
        const auto isCurrentBlockBoxStorage = currentBlock == TileChar::BoxStorage;

        if (nextBlock == TileChar::Empty) {
            // Swap the blocks at the initial coordiante and the destination coordinate
            setTileChar(fromCoordinate, isCurrentBlockBoxStorage ? TileChar::Storage : TileChar::Empty);
            setTileChar(toCoordinate, TileChar::Box);

            if (isCurrentBlockBoxStorage)
                --m_score;

            return true;
        }

        if (nextBlock == TileChar::Storage) {
            // The block at the initial coordiante should become an empty block (or a storage block if
            // the current block is a box-storage block); the block at the destination coordinate should
            // become a box-storage block
            setTileChar(fromCoordinate, isCurrentBlockBoxStorage ? TileChar::Storage : TileChar::Empty);
            setTileChar(toCoordinate, TileChar::BoxStorage);

            // Score increments by 1
            if (!isCurrentBlockBoxStorage)
                ++m_score;

            return true;
        }

        return false;
    }

    void Sokoban::loadSound(const std::string& soundFilename) {
        const auto soundBuffer{ std::make_shared<sf::SoundBuffer>() };
        const auto sound{ std::make_shared<sf::Sound>() };
        if (soundBuffer->loadFromFile(soundFilename)) {
            sound->setBuffer(*soundBuffer);
            m_soundMap[soundFilename] = std::make_pair(sound, soundBuffer);
        }
    }

    void Sokoban::drawResultScreen(sf::RenderTarget& target, sf::RenderStates states) const {
        // Draw "You win!" in the center of the screen
        sf::Text winText;
        winText.setString("You win!");
        winText.setFont(m_font);
        winText.setFillColor(sf::Color(255, 140, 0));
        winText.setCharacterSize(15 * m_width);
        winText.setOutlineColor(sf::Color::White);
        winText.setOutlineThickness(2);

        // Compute the position of winText
        const auto winTextRect = winText.getLocalBounds();
        const float targetWidth = static_cast<float>(target.getSize().x);
        const float targetHeight = static_cast<float>(target.getSize().y);
        winText.setOrigin({ (static_cast<float>(winTextRect.width)) / 2.0f,
                            (static_cast<float>(winTextRect.height)) });
        winText.setPosition({ targetWidth / 2.0f, targetHeight / 2.0f });
        target.draw(winText);

        // Final score
        const auto moveScore = m_width * m_height - m_stateStack.size();
        const auto timeInSeconds = static_cast<double>(m_elapsedTimeInMicroseconds) / 1000000.0;
        const auto timeScore = std::exp(1 - timeInSeconds / std::exp(2));
        const auto finalScore = static_cast<int>(std::floor(moveScore * timeScore * m_score));

        // Draw the score down below the "You win!"
        sf::Text scoreText;
        scoreText.setString("Score: " + std::to_string(finalScore));
        scoreText.setFont(m_font);
        scoreText.setFillColor(sf::Color::Black);
        scoreText.setCharacterSize(3 * m_width);
        scoreText.setOutlineColor(sf::Color::White);
        winText.setOutlineThickness(2);

        // Compute the position of scoreText
        const auto scoreTextRect = scoreText.getLocalBounds();
        scoreText.setOrigin({ static_cast<float>(scoreTextRect.width) / 2.0f,
                              (scoreTextRect.height - static_cast<float>(winTextRect.height)) / 2.0f });
        scoreText.setPosition({ targetWidth / 2.0f, targetHeight / 2.0f });
        target.draw(scoreText);
    }

}  // namespace SB
