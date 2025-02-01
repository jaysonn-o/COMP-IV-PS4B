#ifndef COORDINATE_HPP
#define COORDINATE_HPP

struct Coordinate {
    int x;
    int y;

    bool operator==(const Coordinate& other) const {
        return x == other.x && y == other.y;
    }
};

#endif // COORDINATE_HPP
