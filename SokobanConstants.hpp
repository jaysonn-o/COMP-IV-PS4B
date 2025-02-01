// Copyright 2024 Jason Ossai

#ifndef SOKOBANCONSTANTS_H
#define SOKOBANCONSTANTS_H

#include <string>

/**
 * @brief Sokoban game constants. Include but not limit to the following:
 * 1. The name of the game and the author
 * 2. The size of each tiles
 * 3. Tilesets' filenames
 * 4. Enumeration classes.
 */
namespace SB {

    // The name of the game
    inline const std::string GAME_NAME = "Sokoban";

    // The author name
    inline const std::string AUTHOR_NAME = "Jason Ossai";  // Updated author name

    // The height and width in pixel of each tile
    inline constexpr int TILE_HEIGHT = 64;
    inline constexpr int TILE_WIDTH = 64;

    // Tile characters. In the level (.lvl) files, each character corresponds to a specific texture of
    // has particular meaning to the corresponding position.
    // '@' - The initial position of the player.
    // '.' - An empty space, which the player can move through.
    // '#' - A wall, which blocks movement.
    // 'A' - A box, which can be paused by the player.
    // 'a' - A storage location, where the player is trying to push a box.
    // '1' - A box that is already in a storage location.
    inline constexpr char TILE_CHAR_PLYAER = '@';
    inline constexpr char TILE_CHAR_EMPTY = '.';
    inline constexpr char TILE_CHAR_WALL = '#';
    inline constexpr char TILE_CHAR_BOX = 'A';
    inline constexpr char TILE_CHAR_STORAGE = 'a';
    inline constexpr char TILE_CHAR_BOX_STORAGE = '1';

    // Assets directory
    inline const std::string ASSETS_DIR = "./assets/";

    // Tileset directory
    inline const std::string TILESET_DIR = ASSETS_DIR + "tileset/";

    // Level directory
    inline const std::string LEVEL_DIR = ASSETS_DIR + "level/";

    // Font directory
    inline const std::string FONT_DIR = ASSETS_DIR + "font/";

    // Sound directory
    inline const std::string SOUND_DIR = ASSETS_DIR + "sound/";

    // Tiles filenames
    inline const std::string TILE_ENVIRONMENT_03_FILENAME = TILESET_DIR + "environment_03.png";
    inline const std::string TILE_BLOCK_06_FILENAME = TILESET_DIR + "block_06.png";
    inline const std::string TILE_CRATE_03_FILENAME = TILESET_DIR + "crate_03.png";
    inline const std::string TILE_GROUND_01_FILENAME = TILESET_DIR + "ground_01.png";
    inline const std::string TILE_GROUND_04_FILENAME = TILESET_DIR + "ground_04.png";
    inline const std::string TILE_PLAYER_05_FILENAME = TILESET_DIR + "player_05.png";
    inline const std::string TILE_PLAYER_08_FILENAME = TILESET_DIR + "player_08.png";
    inline const std::string TILE_PLAYER_17_FILENAME = TILESET_DIR + "player_17.png";
    inline const std::string TILE_PLAYER_20_FILENAME = TILESET_DIR + "player_20.png";

    // Fonts filenames
    inline const std::string FONT_DIGITAL7_FILENAME = FONT_DIR + "digital-7.mono.ttf";
    inline const std::string FONT_ROBOTO_FILENAME = FONT_DIR + "roboto-regular.ttf";

    // Sound filenames
    inline const std::string SOUND_BACKGROUND = SOUND_DIR + "background.wav";
    inline const std::string SOUND_WIN = SOUND_DIR + "win.wav";

    /**
     * @brief Enumerates four cardinal directions: Up, Down, Left, and Right. This enumeration follows
     * the naming convention used in SFML.
     */
    enum class Direction { Up, Down, Left, Right };

    /**
     * @brief Enumerates tile characters.
     */
    enum class TileChar : char {
        Player = TILE_CHAR_PLYAER,
        Empty = TILE_CHAR_EMPTY,
        Wall = TILE_CHAR_WALL,
        Box = TILE_CHAR_BOX,
        Storage = TILE_CHAR_STORAGE,
        BoxStorage = TILE_CHAR_BOX_STORAGE,
    };

}  // namespace SB

#endif
