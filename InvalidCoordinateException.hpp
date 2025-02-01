// Copyright 2024 Jason Ossai

#ifndef INVALIDCOORDINATEEXCEPTION_H
#define INVALIDCOORDINATEEXCEPTION_H

#include <string>
#include <SFML/Graphics.hpp>

namespace SB {

    /**
     * @brief This exception is thrown when an invalid coordinate is used.
     */
    class InvalidCoordinateException final : public std::exception {
    public:
        /**
         * @brief Creates an InvalidCoordinateException instance.
         * @param coordinate The invalid coordinate.
         */
        explicit InvalidCoordinateException(const sf::Vector2i& coordinate) noexcept;

        /**
         * @brief Gets the exception message.
         */
        [[nodiscard]] const char* what() const noexcept override;

    private:
        /**
         * @brief The exception message to display.
         */
        std::string message;
    };

}  // namespace SB

#endif
