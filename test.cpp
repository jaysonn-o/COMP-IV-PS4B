// Copyright 2024 Jason Ossai

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <boost/test/unit_test.hpp>
#include "Sokoban.hpp"

/**
 * @brief Checks if two coordinates are the same.
 * @param first The first coordinate.
 * @param second The second coordinate.
 * @return True if the two components of the two coordinates are equal respectively; false
 * otherwise.
 */
bool isCoordinateEqual(const sf::Vector2u& first, const sf::Vector2u& second) noexcept {
    return first.x == second.x && first.y == second.y;
}

// Tests if `height()` and `width()` returns the height and width of a map correctly.
BOOST_AUTO_TEST_CASE(testHeightWidth) {
    const SB::Sokoban sokoban{ "assets/level/level2.lvl" };

    BOOST_REQUIRE_EQUAL(sokoban.height(), 10);
    BOOST_REQUIRE_EQUAL(sokoban.width(), 12);
}

// Tests if `playerLoc()` returns the correct player location in the beginning of the game.
BOOST_AUTO_TEST_CASE(testPlayerPosition) {
    const SB::Sokoban sokoban{ "assets/level/level2.lvl" };

    BOOST_REQUIRE(isCoordinateEqual(sokoban.playerLoc(), { 8, 5 }));
}

// Tests if `movePlayer(SB::Direction)` works correctly: a player should be able to push a box if
// the box is not blocked by a wall or another box.
BOOST_AUTO_TEST_CASE(testMovePlayer) {
    SB::Sokoban sokoban{ "assets/level/level2.lvl" };
    sokoban.movePlayer(SB::Direction::Right);

    BOOST_REQUIRE(isCoordinateEqual(sokoban.playerLoc(), { 9, 5 }));
}

// Tests if `movePlayer(SB::Direction)` works correctly: a player should not push a box that is
// blocked by another box.
BOOST_AUTO_TEST_CASE(testMovePlayerBlockedByBox) {
    SB::Sokoban sokoban{ "assets/level/level2.lvl" };

    // Since there are two boxes in a row in the up direction, the player is not able to move no
    // matter how many times they try to move upwards.
    sokoban.movePlayer(SB::Direction::Up);
    sokoban.movePlayer(SB::Direction::Up);

    BOOST_REQUIRE(isCoordinateEqual(sokoban.playerLoc(), { 8, 5 }));
}

// Tests if `movePlayer(SB::Direction)` works correctly: a player should not push a box that is
// blocked by a wall block.
BOOST_AUTO_TEST_CASE(testMovePlayerBlockedByWall) {
    SB::Sokoban sokoban{ "assets/level/level2.lvl" };

    // Move rightward twice. For the first move, the player pushes the box rightwards;
    // For the second move, the player stays on the spot, as the box cannot be pushed
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Right);

    BOOST_REQUIRE(isCoordinateEqual(sokoban.playerLoc(), { 9, 5 }));
}

// Tests if `movePlayer(SB::Direction)` works correctly: a player should not move out of the map
// from the upper border.
BOOST_AUTO_TEST_CASE(testMovePlayerUpBorder) {
    SB::Sokoban sokoban{ "assets/level/swapoff.lvl" };
    sokoban.movePlayer(SB::Direction::Left);
    sokoban.movePlayer(SB::Direction::Up);
    sokoban.movePlayer(SB::Direction::Up);
    sokoban.movePlayer(SB::Direction::Up);

    BOOST_REQUIRE(isCoordinateEqual(sokoban.playerLoc(), { 1, 0 }));
}

// Tests if `movePlayer(SB::Direction)` works correctly: a player should not move out of the map
// from the right border.
BOOST_AUTO_TEST_CASE(testMovePlayerRightBorder) {
    SB::Sokoban sokoban{ "assets/level/swapoff.lvl" };
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Right);

    BOOST_REQUIRE(isCoordinateEqual(sokoban.playerLoc(), { 4, 2 }));
}

// Tests if `movePlayer(SB::Direction)` works correctly: a player should not move out of the map
// from the down border.
BOOST_AUTO_TEST_CASE(testMovePlayerDownBorder) {
    SB::Sokoban sokoban{ "assets/level/swapoff.lvl" };
    sokoban.movePlayer(SB::Direction::Down);
    sokoban.movePlayer(SB::Direction::Down);
    sokoban.movePlayer(SB::Direction::Down);

    BOOST_REQUIRE(isCoordinateEqual(sokoban.playerLoc(), { 2, 4 }));
}

// Tests if `movePlayer(SB::Direction)` works correctly: a player should not move out of the map
// from the left border.
BOOST_AUTO_TEST_CASE(testMovePlayerLeftBorder) {
    SB::Sokoban sokoban{ "assets/level/swapoff.lvl" };
    sokoban.movePlayer(SB::Direction::Left);
    sokoban.movePlayer(SB::Direction::Left);
    sokoban.movePlayer(SB::Direction::Left);

    BOOST_REQUIRE(isCoordinateEqual(sokoban.playerLoc(), { 0, 2 }));
}

// Tests if `movePlayer(SB::Direction)` works correctly: a player should not push a box out of the
// map.
BOOST_AUTO_TEST_CASE(testMovePlayerPushBoxOffScreen) {
    SB::Sokoban sokoban{ "assets/level/swapoff.lvl" };

    // Try to push a box out of the map, the player should stay on the spot in the second move
    sokoban.movePlayer(SB::Direction::Up);
    sokoban.movePlayer(SB::Direction::Up);

    BOOST_REQUIRE(isCoordinateEqual(sokoban.playerLoc(), { 2, 1 }));
}

// Tests if `isWon()` works correctly: If all boxes are already in the storages, it should return
// true.
BOOST_AUTO_TEST_CASE(testIsWon) {
    const SB::Sokoban sokoban{ "assets/level/autowin2.lvl" };

    BOOST_REQUIRE(sokoban.isWon());
}

// Tests if `isWon()` works correctly: If there are two boxes and only one storage, players win
// as long as they push one box to the storage.
BOOST_AUTO_TEST_CASE(testIsWonTooManyBoxes) {
    SB::Sokoban sokoban{ "assets/level/level5.lvl" };
    sokoban.movePlayer(SB::Direction::Up);
    sokoban.movePlayer(SB::Direction::Up);
    sokoban.movePlayer(SB::Direction::Up);
    sokoban.movePlayer(SB::Direction::Up);
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Down);
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Up);

    BOOST_REQUIRE(sokoban.isWon());
}

// Tests if `isWon()` works correctly: If there are three storages but only two boxes, players win
// when they stow the boxes properly.
BOOST_AUTO_TEST_CASE(testIsWonTooManyStorages) {
    SB::Sokoban sokoban{ "assets/level/level6.lvl" };
    sokoban.movePlayer(SB::Direction::Up);
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Up);
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Down);
    sokoban.movePlayer(SB::Direction::Down);
    sokoban.movePlayer(SB::Direction::Left);
    sokoban.movePlayer(SB::Direction::Left);
    sokoban.movePlayer(SB::Direction::Left);
    sokoban.movePlayer(SB::Direction::Left);
    sokoban.movePlayer(SB::Direction::Up);
    sokoban.movePlayer(SB::Direction::Up);
    sokoban.movePlayer(SB::Direction::Up);
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Up);
    sokoban.movePlayer(SB::Direction::Left);

    BOOST_REQUIRE(sokoban.isWon());
}
