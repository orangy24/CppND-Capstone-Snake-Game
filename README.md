# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

This is a classic Snake game implementation using C++ and SDL (Simple DirectMedia Layer) library. In this version, a Bomb feature is added to the game. The game window is rendered using SDL.

## Folder structure
.
├── CMakeLists.txt
├── CODEOWNERS
├── LICENSE.md
├── README.md
├── background.bmp
├── cmake
│   └── FindSDL2_image.cmake
├── include
│   ├── controller.h
│   ├── game.h
│   ├── game_object
│   │   ├── IGameObject.h
│   │   ├── bomb.h
│   │   ├── food.h
│   │   └── snake.h
│   └── renderer.h
├── snake_game.gif
└── src
    ├── controller.cpp
    ├── game.cpp
    ├── game_object
    │   ├── bomb.cpp
    │   ├── food.cpp
    │   └── snake.cpp
    ├── main.cpp
    └── renderer.cpp

5 directories, 21 files

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Game Controls
Use the arrow keys to move the snake.
Press 'p' to pause the game.
Press 'q' to quit the game.
### Bomb Feature
In this version of the game, Bombs will be spawned randomly and they will explode after a certain time, killing the snake if it's caught in the explosion range.

## Game Rules
The objective of the game is to control the snake to eat as many apples as possible.
Each apple eaten will increase the snake's length.
The game ends when the snake hits the wall or its own body, or is killed by the explosion of a bomb.
The longer the snake becomes, the more difficult it is to avoid colliding with itself.

## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
