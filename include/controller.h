#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "game_object/snake.h"
#include <condition_variable>

class Controller {
 public:
  void HandleInput(bool &running, bool& pause, Snake* snake_ptr) const;

 private:
  void ChangeDirection(Snake* snake_ptr, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif