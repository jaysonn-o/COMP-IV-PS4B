// Copyright 2024 Jason Ossai

#ifndef SOKOBANSCORE_HPP
#define SOKOBANSCORE_HPP

#include <SFML/Graphics.hpp>

namespace SB {

    /**
     * @brief This class manages the score system in Sokoban.
     */
    class SokobanScore : public virtual sf::Drawable {
    public:
        /**
         * @brief Creates a SokobanScore instance; initializes the font.
         */
        SokobanScore();

        /**
         * @brief Checks if the player has won the game.
         * @return True if the player has won the game; false otherwise.
         */
        bool isWon() const;

    protected:
        /**
         * @brief Draws the score and the max score onto the target.
         */
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        /**
         * @brief The player's current score. Players get one score when they successfully put a box to
         * a storage. In a word, the score is equal to the number of "StorageBox" blocks in the map.
         */
        int m_score = 0;

        /**
         * @brief The player's max score in the current level. The player wins the game when the score
         * equals the max score.
         */
        int m_maxScore = 1;

        /**
         * @brief The font for the displayed text.
         */
        sf::Font m_font;
    };

}  // namespace SB

#endif
