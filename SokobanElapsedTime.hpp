// Copyright 2024 Jason Ossai

#ifndef SOKOBANELAPSEDTIME_H
#define SOKOBANELAPSEDTIME_H

#include <SFML/Graphics.hpp>

namespace SB {

    /**
     * @brief This class manages the elapsed time system in Sokoban.
     */
    class SokobanElapsedTime : virtual public sf::Drawable {
    public:
        /**
         * @brief Creates a SokobanElapsedTime instance: initializes the font.
         */
        SokobanElapsedTime();

        /**
         * @brief Updates the game in a game frame. This will update the elapsed time.
         * @param dt The delta time in microseconds between this frame and the previous frame.
         */
        virtual void update(const int64_t& dt);

    protected:
        /**
         * @brief Draws the elapsed time in the format of "H:MM:SS" in the upper-left corner.
         */
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        /**
         * @brief The elapsed time in microseconds.
         */
        int64_t m_elapsedTimeInMicroseconds = 0;

        /**
         * @brief The font for the displayed text.
         */
        sf::Font m_font;
    };

}  // namespace SB

#endif
