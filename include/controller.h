#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "game_object/snake.h"

class Controller {
 public:
  void HandleInput(bool &running, Snake* snake_ptr) const;

 private:
  void ChangeDirection(Snake* snake_ptr, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif