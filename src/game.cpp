#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : grid_width_(grid_width),
      grid_height_(grid_height),
      snake_(std::make_unique<Snake>(grid_width, grid_height)),
      food_(std::make_unique<Food>(grid_width, grid_height)) {
    //TODO: create game objects into vector
    //1. spwan snake
    //2. place food
    food_->PlaceFood(snake_.get());

}
void Game::SetGameHandler(Controller* controller, Renderer* renderer,
           std::size_t target_frame_duration) {
    controller_handler = controller;
    renderer_handler = renderer;
    target_frame_duration_ = target_frame_duration;
}

void Game::Run() {
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    running_ = true;

    while (running_) {
      // if (!snake_->isAlive()) break;
      frame_start = SDL_GetTicks();
      if (snake_->isAlive() && rand() % BOMB_SPAWN_RATE == 0) {
          SpawnBomb();
      }
      // Input, Update, Render - the main game loop.
      controller_handler->HandleInput(running_, snake_.get());
      Update();
      renderer_handler->Render(snake_.get(), food_.get(), bombs_);

      frame_end = SDL_GetTicks();

      // Keep track of how long each loop through the input/update/render cycle
      // takes.
      frame_count++;
      frame_duration = frame_end - frame_start;

      // After every second, update the window title.
      if (frame_end - title_timestamp >= 1000) {
          renderer_handler->UpdateWindowTitle(score, frame_count);
          frame_count = 0;
          title_timestamp = frame_end;
      }

      // If the time for this frame is too small (i.e. frame_duration is
      // smaller than the target ms_per_frame), delay the loop to
      // achieve the correct frame rate.
      if (frame_duration < target_frame_duration_) {
          SDL_Delay(target_frame_duration_ - frame_duration);
      }
  }
}
void Game::SpawnBomb() {
    std::lock_guard<std::mutex> lock(mtx_);
    int number_of_bomb = rand() % BOMB_SPAWN_NUMBER;  
    for (int i = 0; i < number_of_bomb; i++) {
        auto new_bomb = std::make_shared<Bomb>(grid_width_, grid_height_);
        new_bomb->Spawn(snake_.get());
        bombs_.emplace_back(std::move(new_bomb));
    }

}
void Game::Update() {
    if (!snake_->isAlive()) return;
    snake_->Update();
    auto snake_head = snake_->GetSnakeHead();
    int new_x = static_cast<int>(snake_head.x);
    int new_y = static_cast<int>(snake_head.y);
    for (const auto& bomb : bombs_) {
        if ((bomb->isExploding() && bomb->collidesWithExplosion(snake_.get())) ||
            bomb->collidesWithoutExplosion(snake_.get())) {
            snake_->Kill();
        } 
    }
    {
      std::lock_guard<std::mutex> lock(mtx_);
      auto removeBomb = [&](std::shared_ptr<Bomb> bomb) -> bool {
          return bomb->CoolDown();
      };
      bombs_.remove_if(removeBomb);
    }
    
    // Check if there's food over here
    // snake check collide with food
    auto food_pos = food_->GetFoodPosition();
    // std::cout<<"food pos: "<<food_pos.x<<" "<<food_pos.y<<std::endl;
    // std::cout<<"snake pos: "<<new_x<<" "<<new_x<<std::endl;
    if (food_pos.x == new_x && food_pos.y == new_y) {
      score++;
      food_->PlaceFood(snake_.get());
      // Grow snake and increase speed.
      snake_->GrowBody();
      snake_->UpdateSpeed(0.02);
    }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake_->GetSnakeSize(); }