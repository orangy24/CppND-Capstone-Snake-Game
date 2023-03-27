#ifndef BOMB_H
#define BOMB_H

#include "IGameObject.h"
#include "snake.h"
#include <random>

#include <thread>
#include <future>
#include <iostream>
// Define the Bomb class
class Bomb {
  public:
    Bomb(std::size_t grid_width, std::size_t grid_height)
        : grid_width_(grid_width),
          grid_height_(grid_height),
          engine(dev()),
          random_w(0, static_cast<int>(grid_width - 1)),
          random_h(0, static_cast<int>(grid_height - 1)) {
            size_ = 20;
            countdown_ = 3500; // 3.5 seconds
            exploding_ = false;
    }
    ~Bomb() {}
    void Spawn(Snake* snake);

    void Draw(SDL_Renderer* renderer, SDL_Rect& block);

    void DrawExplode(SDL_Renderer* renderer, SDL_Rect& block);

    bool collidesWithExplosion(Snake* );
    bool collidesWithoutExplosion(Snake* );
    void startTimer(int );

    void timer(std::promise<void> promiseObj);

    bool CoolDown();
    bool isExploding() const {
        return exploding_;
    }

    std::future<void> futureObj_;

 private:
    void count_down(int dt);
    uint32_t explode_time_;
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;
    int x_, y_;
    int size_, countdown_;
    uint32_t exlode_duration_{1500}; // 1s
    bool exploding_;
    int grid_width_;
    int grid_height_;
};

// // In the main game loop:
// std::vector<Bomb> bombs;

// // Spawn a bomb
// Bomb bomb(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
// bombs.push_back(bomb);

// // Draw the bombs
// for (int i = 0; i < bombs.size(); i++) {
//     bombs[i].draw(renderer);
// }

// // Check for collision with the snake
// for (int i = 0; i < bombs.size(); i++) {
//     if (bombs[i].collidesWithSnake(snake)) {
//         bombs[i].startTimer();
//         // The game will continue while the bomb timer runs in a separate thread
//     }
// }

// // When the bomb explodes
// if (bombs[i].exploded) {
//     // Create an explosion effect
//     // ...

//     // Check for collision with the snake
//     if (bombs[i].collidesWithSnake(snake)) {
//         // The snake dies
//         // ...
//     }

//     // Remove the bomb from the list
//     bombs.erase(bombs.begin() + i);
// }

// // When the snake eats a bomb
// if (snake.collides


#endif