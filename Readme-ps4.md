# PS4b: Sokoban

## Contact
Name:Jason Ossai
Section: COMP IV 2040
Time to Complete: Couple of Days


## Description
Part B of the Sokoban project introduces enhanced gameplay mechanics, allowing players to move and push boxes into designated storage areas using WASD or arrow keys.

### Features
The development process involved several significant decisions, including:

#### Movement
-The player can navigate in four cardinal directions using WASD or arrow keys, assuming the destination is an open space.
-The Sokoban class has a `movePlayer` method that uses a `Direction` enumeration constant as a parameter.

### Memory
Smart pointers are not required for low memory utilization because the game grid is represented by a two-dimensional vector of characters for level data storage.

#### Box Interactions
- Although boxes can be pushed into open areas, they will obstruct mobility if they are next to a wall or another box.
- Only one box can be pushed by the player at once.

  
#### Game Mechanics
- To win the game, the player has to push every box into its designated storage space.
- The `isWon()` function determines whether the player has accomplished this objective, and upon success, it displays a congratulations message.
-If players find themselves in an unwinnable predicament, they can attempt again by pressing `R`, which returns the level to its initial state.

### Unit Tests
Unit tests have been developed to validate the Sokoban model, ensuring correct movement mechanics, box interactions, and victory conditions, using level files to assess functionality without user input.

### Issues
I had lots of lint and valgrind errors which I was unable to fix all. By doing so it changes my code and gives more errors. The errors were about 137, which became so much for me to fix without messing up the code for my sokoban.

### Extra Credit
I attempted some extra credit for the first time, by adding sound to the gameplay, which you can find the mp3 sound file in my assets folder under sound.
I Also made the player to change direction while moving .


## Acknowledgements
I did this project myself without any help.
If you used images or other resources than the ones provided, list them here.

Digital 7 Font: https://www.dafont.com/digital-7.font
Font: https://fonts.google.com/specimen/Roboto
Pixel Perfect (background music): https://elements.envato.com/pixel-perfect-LMWJFGY
Win Game Sound (game-winning sound effect): https://elements.envato.com/win-game-sound-WASB34G


##Resources
Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban
All resource files are placed in my assets directory.

