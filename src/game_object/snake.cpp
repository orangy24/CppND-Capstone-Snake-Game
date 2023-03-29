#include "game_object/snake.h"
#include <cmath>

void Snake::Draw(SDL_Renderer* sdl_renderer, SDL_Rect& block) {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for (SDL_Point const &point : this->body) {
        block.x = point.x * block.w;
        block.y = point.y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
    }

    // Render snake's head
    block.x = static_cast<int>(head_pos_.x) * block.w;
    block.y = static_cast<int>(head_pos_.y) * block.h;
    if (this->alive_) {
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    } else {
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    }
    SDL_RenderFillRect(sdl_renderer, &block);
}
void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_pos_.x),
      static_cast<int>(
          head_pos_.y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_pos_.x),
      static_cast<int>(head_pos_.y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {

    switch (direction) {
      case Direction::kUp:
        head_pos_.y -= speed_;
        break;

      case Direction::kDown:
        head_pos_.y += speed_;
        break;

      case Direction::kLeft:
        head_pos_.x -= speed_;
        break;

      case Direction::kRight:
        head_pos_.x += speed_;
        break;
    }

    // Wrap the Snake around to the beginning if going off of the screen.
    head_pos_.x = fmod(head_pos_.x + grid_width_, grid_width_);
    head_pos_.y = fmod(head_pos_.y + grid_height_, grid_height_);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
    // Add previous head location to vector
    body.push_back(prev_head_cell);

    if (!growing_) {
        // Remove the tail from the vector.
        body.erase(body.begin());
    } else {
        growing_ = false;
        size_++;
    }

    // Check if the snake has died.
    for (auto const &item : body) {
        if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
            alive_ = false;
        }
    }
}
void Snake::UpdateSpeed(float s) {
    speed_ += s;
}
void Snake::GrowBody() { growing_ = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_pos_.x) && y == static_cast<int>(head_pos_.y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}