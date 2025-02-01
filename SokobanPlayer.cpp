// Copyright 2024 Jason Ossai

#include "SokobanPlayer.hpp"
#include <memory>

namespace SB {

    SokobanPlayer::SokobanPlayer() {
        const auto playerUpTexture{ std::make_shared<sf::Texture>() };
        const auto playerRightTexture{ std::make_shared<sf::Texture>() };
        const auto playerDownTexture{ std::make_shared<sf::Texture>() };
        const auto playerLeftTexture{ std::make_shared<sf::Texture>() };
        playerUpTexture->loadFromFile(TILE_PLAYER_08_FILENAME);
        playerRightTexture->loadFromFile(TILE_PLAYER_17_FILENAME);
        playerDownTexture->loadFromFile(TILE_PLAYER_05_FILENAME);
        playerLeftTexture->loadFromFile(TILE_PLAYER_20_FILENAME);

        m_playerTextureMap[Direction::Up] = { playerUpTexture };
        m_playerTextureMap[Direction::Right] = { playerRightTexture };
        m_playerTextureMap[Direction::Down] = { playerDownTexture };
        m_playerTextureMap[Direction::Left] = { playerLeftTexture };

        const auto playerUpSprite{ std::make_shared<sf::Sprite>() };
        const auto playerRightSprite{ std::make_shared<sf::Sprite>() };
        const auto playerDownSprite{ std::make_shared<sf::Sprite>() };
        const auto playerLeftSprite{ std::make_shared<sf::Sprite>() };
        playerUpSprite->setTexture(*playerUpTexture);
        playerRightSprite->setTexture(*playerRightTexture);
        playerDownSprite->setTexture(*playerDownTexture);
        playerLeftSprite->setTexture(*playerLeftTexture);

        m_playerSpriteMap[Direction::Up] = playerUpSprite;
        m_playerSpriteMap[Direction::Right] = playerRightSprite;
        m_playerSpriteMap[Direction::Down] = playerDownSprite;
        m_playerSpriteMap[Direction::Left] = playerLeftSprite;
    }

    void SokobanPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        const auto player = m_playerSpriteMap.at(m_playerOrientation);
        player->setPosition({
            static_cast<float>(m_playerLoc.x * TILE_WIDTH),
            static_cast<float>(m_playerLoc.y * TILE_HEIGHT),
            });
        target.draw(*player);
    }

    sf::Vector2u SokobanPlayer::playerLoc() const {
        return { static_cast<unsigned>(m_playerLoc.x), static_cast<unsigned>(m_playerLoc.y) };
    }

}  // namespace SB
