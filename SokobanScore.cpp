// Copyright 2024 Jason Ossai

#include "SokobanScore.hpp"
#include <string>
#include "SokobanConstants.hpp"

namespace SB {

    SokobanScore::SokobanScore() { m_font.loadFromFile(FONT_DIGITAL7_FILENAME); }

    bool SokobanScore::isWon() const { return m_score == m_maxScore; }

    void SokobanScore::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        const std::string stringToPrint = std::to_string(m_score) + "/" + std::to_string(m_maxScore);

        sf::Text text;
        text.setFont(m_font);
        text.setString(stringToPrint);
        text.setCharacterSize(28);
        text.setFillColor(isWon() ? sf::Color::Green : sf::Color::Red);
        text.setPosition(target.getSize().x - 60, 10);
        target.draw(text);
    }

}  // namespace SB
