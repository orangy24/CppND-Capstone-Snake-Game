#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake_(std::make_unique<Snake>(grid_width, grid_height)),
      food_(std::make_unique<Food>(grid_width, grid_height)),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
    //TODO: create game objects into vector
    //1. spwan snake
    //2. place food
    food_->PlaceFood(snake_.get());
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;

    while (running) {
      frame_start = SDL_GetTicks();

      // Input, Update, Render - the main game loop.
      controller.HandleInput(running, snake_.get());
      Update();
      renderer.Render(snake_.get(), food_.get());

      frame_end = SDL_GetTicks();

      // Keep track of how long each loop through the input/update/render cycle
      // takes.
      frame_count++;
      frame_duration = frame_end - frame_start;

      // After every second, update the window title.
      if (frame_end - title_timestamp >= 1000) {
          renderer.UpdateWindowTitle(score, frame_count);
          frame_count = 0;
          title_timestamp = frame_end;
      }

      // If the time for this frame is too small (i.e. frame_duration is
      // smaller than the target ms_per_frame), delay the loop to
      // achieve the correct frame rate.
      if (frame_duration < target_frame_duration) {
          SDL_Delay(target_frame_duration - frame_duration);
      }
  }
}

void Game::Update() {
    if (!snake_->isAlive()) return;

    snake_->Update();
    auto snake_head = snake_->GetSnakeHead();
    int new_x = static_cast<int>(snake_head.x);
    int new_y = static_cast<int>(snake_head.y);

    // Check if there's food over here
    // snake check collide with food
    auto food_pos = food_->GetFoodPosition();
    // std::cout<<"food pos: "<<food_pos.x<<" "<<food_pos.y<<std::endl;
    // std::cout<<"snake pos: "<<new_x<<" "<<new_x<<std::endl;
    if (food_pos.x == new_x && food_pos.y == new_y) {
      // std::cout<<"hitt"<<std::endl;
      score++;
      food_->PlaceFood(snake_.get());
      // Grow snake and increase speed.
      snake_->GrowBody();
      snake_->UpdateSpeed(0.02);
    }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake_->GetSnakeSize(); }