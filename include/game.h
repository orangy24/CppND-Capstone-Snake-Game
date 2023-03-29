#ifndef GAME_H
#define GAME_H

#include <random>
#include <list>
#include <thread>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "game_object/snake.h"
#include "game_object/food.h"
#include "game_object/bomb.h"

static constexpr int BOMB_SPAWN_RATE = 150;
static constexpr int BOMB_SPAWN_NUMBER = 3;
class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  ~Game() {}
  void Run();
  int GetScore() const;
  int GetSize() const;

  void SetGameHandler(Controller* controller, Renderer* renderer,
           std::size_t target_frame_duration);

 private:
  
  std::size_t grid_width_;
  std::size_t grid_height_;

  Controller* controller_handler;
  Renderer* renderer_handler;
  std::size_t target_frame_duration_;

  bool running_{false};
  //game objects
  std::unique_ptr<Snake> snake_;
  std::unique_ptr<Food> food_;
  std::list<std::shared_ptr<Bomb>> bombs_;

  std::thread game_loop_thread_;
  std::thread bomb_spwan_thread_;
  std::condition_variable cv_;
  std::mutex mtx_;
  bool paused_ = false;

  int score{0};
  void Update();
  void SpawnBomb();
};

#endif