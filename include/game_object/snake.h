#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

#include "IGameObject.h"

//TODO: add base class game object
class Snake : public IGameObject {
  public:
    enum class Direction { kUp = 0, kDown, kLeft, kRight };

    Snake(int grid_width, int grid_height)
        : grid_width(grid_width),
          grid_height(grid_height),
          head_pos_({grid_width / 2.0f, grid_height / 2.0f}) 
          {}
  
    Snake(const Snake& other) = delete;
    Snake(const Snake&& other) = delete;
    Snake& operator=(const Snake& other) = delete;
    Snake& operator=(const Snake&& other) = delete;

    void Update();
    void Draw(SDL_Renderer* sdl_renderer, SDL_Rect& block);

    void GrowBody();
    void UpdateSpeed(float speed);
    bool SnakeCell(int x, int y);
    
    bool isAlive() const {
        return alive_;
    }
    SDL_FPoint GetSnakeHead() const {
        return head_pos_;
    }
    int GetSnakeSize() const {
        return size_;
    }
    Direction direction = Direction::kUp;
    std::vector<SDL_Point> body;

  private:
    void UpdateHead();
    void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

    float speed_{0.1f};
    int size_{1};
    bool alive_{true};

    SDL_FPoint head_pos_;

    bool growing{false};
    int grid_width;
    int grid_height;
};

#endif