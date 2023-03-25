#ifndef FOOD_H
#define FOOD_H

#include "IGameObject.h"
#include "snake.h"
#include <random>
#include <iostream>

class Food : public IGameObject {
  public:
    Food(std::size_t grid_width, std::size_t grid_height)
        : grid_width_(grid_width),
          grid_height_(grid_height),
          engine(dev()),
          random_w(0, static_cast<int>(grid_width - 1)),
          random_h(0, static_cast<int>(grid_height - 1))
          {}

    Food(const Food& other) = delete;
    Food(const Food&& other) = delete;
    Food& operator=(const Food& other) = delete;
    Food& operator=(const Food&& other) = delete;

    void Update() {};
    void Draw(SDL_Renderer* sdl_renderer, SDL_Rect& block);
    void PlaceFood(Snake* snake);
    SDL_Point GetFoodPosition() const {
        return food_pos_;
    }
  private:
    SDL_Point food_pos_;
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;

    int grid_width_;
    int grid_height_;
};
#endif