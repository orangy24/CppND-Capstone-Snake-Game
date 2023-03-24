#include "game_object/food.h"

void Food::PlaceFood(Snake* snake) {
    int x, y;
    while (true) {
        x = random_w(engine);
        y = random_h(engine);
        // Check that the location is not occupied by a snake item before placing
        // food.
        if (!snake->SnakeCell(x, y)) {
          this->food_pos_.x = x;
          this->food_pos_.y = y;
          return;
        }
    }
}

void Food::Draw(SDL_Renderer* sdl_renderer, SDL_Rect& block) {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    block.x = this->food_pos_.x * block.w;
    block.y = this->food_pos_.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
}