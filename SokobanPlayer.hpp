// Copyright 2024 Jason Ossai

#ifndef SOKOBANPLAYER_HPP
#define SOKOBANPLAYER_HPP

#include <memory>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "SokobanConstants.hpp"

namespace SB {

    /**
     * @brief This class manages the player system in Sokoban.
     */
    class SokobanPlayer : public virtual sf::Drawable {
    public:
        /**
         * @brief Returns the players' current position; (0, 0) represents the upper-left cell in the
         * upper-left corner.
         */
        [[nodiscard]] sf::Vector2u playerLoc() const;

    protected:
        /**
         * @brief Creates a SokobanPlayer instance; initializes the player texture map and the player
         * sprite map.
         */
        SokobanPlayer();

        /**
         * @brief Draws the player onto the target.
         */
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        /**
         * @brief The player's default orientation.
         */
        inline static Direction DEFAULT_ORIENTATION = Direction::Down;

        /**
         * @brief Player location. Note the unit of this coordinate is tile instead of pixel.
         */
        sf::Vector2i m_playerLoc = { 0, 0 };

        /**
         * @brief Associates each direction with the corresponding player texture.
         */
        std::unordered_map<Direction, std::shared_ptr<sf::Texture>> m_playerTextureMap;

        /**
         * @brief Associates each direction with the corresponding player sprite. Player sprites vary
         * depending on the orientation.
         */
        std::unordered_map<Direction, std::shared_ptr<sf::Sprite>> m_playerSpriteMap;

        /**
         * @brief Player's current orientation. The default orientation is down.
         */
        Direction m_playerOrientation = DEFAULT_ORIENTATION;
    };

}  // namespace SB

#endif
