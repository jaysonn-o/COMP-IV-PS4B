// Copyright 2024 Jason Ossai

#include "InvalidCoordinateException.hpp"
#include <sstream>

namespace SB {

    InvalidCoordinateException::InvalidCoordinateException(const sf::Vector2i& coordinate) noexcept {
        std::ostringstream oss;
        oss << "Invalid coordinate: (" << coordinate.x << ", " << coordinate.y << ")";
        message = oss.str();
    }

    const char* InvalidCoordinateException::what() const noexcept { return message.c_str(); }

}  // namespace SB
