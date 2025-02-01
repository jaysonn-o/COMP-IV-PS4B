// Copyright 2024 Jason Ossai

#include "SokobanTileGrid.hpp"
#include <memory>
#include <SFML/Graphics.hpp>
#include "InvalidCoordinateException.hpp"

namespace SB {

    SokobanTileGrid::SokobanTileGrid() {
        const auto groundTexture{ std::make_shared<sf::Texture>() };
        const auto groundStorageTexture{ std::make_shared<sf::Texture>() };
        const auto boxTexture{ std::make_shared<sf::Texture>() };
        const auto wallTexture{ std::make_shared<sf::Texture>() };
        groundTexture->loadFromFile(TILE_GROUND_01_FILENAME);
        groundStorageTexture->loadFromFile(TILE_GROUND_04_FILENAME);
        boxTexture->loadFromFile(TILE_CRATE_03_FILENAME);
        wallTexture->loadFromFile(TILE_BLOCK_06_FILENAME);

        m_tileTextureMap[TileChar::Player] = { groundTexture };
        m_tileTextureMap[TileChar::Empty] = { groundTexture };
        m_tileTextureMap[TileChar::Wall] = { wallTexture };
        m_tileTextureMap[TileChar::Box] = { boxTexture };
        m_tileTextureMap[TileChar::Storage] = { groundStorageTexture };
        m_tileTextureMap[TileChar::BoxStorage] = { boxTexture };
    }

    void SokobanTileGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        traverseTileCharGrid([&](auto coordinate, auto tileChar) {
            const sf::Vector2f position({ static_cast<float>(coordinate.x * TILE_WIDTH),
                                          static_cast<float>(coordinate.y * TILE_HEIGHT) });
            const auto tile = getTile(tileChar);
            tile->setPosition(position);
            target.draw(*tile);

            return false;
            });
    }

    int SokobanTileGrid::getIndex(const sf::Vector2i& coordinate) const {
        return coordinate.x + coordinate.y * m_width;
    }

    int SokobanTileGrid::height() const { return m_height; }

    int SokobanTileGrid::width() const { return m_width; }

    TileChar SokobanTileGrid::getTileChar(const sf::Vector2i& coordinate) const {
        return m_tileCharGrid.at(checkCoordinate(coordinate));
    }

    void SokobanTileGrid::setTileChar(const sf::Vector2i& coordinate, const TileChar tileChar) {
        const auto index = checkCoordinate(coordinate);
        const auto originalTileChar = m_tileCharGrid[index];

        if (originalTileChar != tileChar) {
            m_tileCharGrid[index] = tileChar;
            const auto newTile{ std::make_shared<sf::Sprite>() };
            newTile->setTexture(*m_tileTextureMap.at(tileChar));
        }
    }

    void SokobanTileGrid::traverseTileCharGrid(
        const std::function<bool(sf::Vector2i, TileChar)>& callback) const {
        auto stopIteration = false;
        for (int row = 0; !stopIteration && row < m_height; ++row) {
            for (int col = 0; !stopIteration && col < m_width; ++col) {
                const auto tileChar = getTileChar({ col, row });
                stopIteration = callback({ col, row }, tileChar);
            }
        }
    }

    std::shared_ptr<sf::Sprite> SokobanTileGrid::getTile(const TileChar& tileChar) const {
        const auto it = m_tileTextureMap.find(tileChar);
        if (it == m_tileTextureMap.end()) {
            return nullptr;
        }

        const auto sprite{ std::make_shared<sf::Sprite>() };
        sprite->setTexture(*it->second);

        return sprite;
    }

    int SokobanTileGrid::checkCoordinate(const sf::Vector2i& coordinate) const {
        const auto index = getIndex(coordinate);
        const auto gridSize = static_cast<int>(m_initialTileCharGrid.size());
        if (index < 0 || index >= gridSize) {
            throw InvalidCoordinateException(coordinate);
        }

        return index;
    }

}  // namespace SB
