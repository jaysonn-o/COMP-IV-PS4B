// Copyright 2024 Jason Ossai

#include "SokobanElapsedTime.hpp"
#include <string>
#include "SokobanConstants.hpp"

namespace SB {

    SokobanElapsedTime::SokobanElapsedTime() { m_font.loadFromFile(FONT_DIGITAL7_FILENAME); }

    void SokobanElapsedTime::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        const unsigned seconds = m_elapsedTimeInMicroseconds / 1000000u;
        const unsigned minutes = seconds / 60u;
        const unsigned hours = minutes / 60u;
        const unsigned second = seconds % 60u;
        const unsigned minute = minutes % 60u;
        const std::string secondStr = (second < 10 ? "0" : "") + std::to_string(second);
        const std::string minuteStr = (minute < 10 ? "0" : "") + std::to_string(minute);
        const std::string hourStr = std::to_string(hours);
        const std::string stringToPrint = hourStr + ":" + minuteStr + ":" + secondStr;

        sf::Text text;
        text.setFont(m_font);
        text.setString(stringToPrint);
        text.setCharacterSize(28);
        text.setFillColor(sf::Color::Black);
        text.setPosition(15, 10);
        target.draw(text);
    }

    void SokobanElapsedTime::update(const int64_t& dt) { m_elapsedTimeInMicroseconds += dt; }

}  // namespace SB
