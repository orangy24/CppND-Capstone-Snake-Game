#ifndef FOOD_H
#define FOOD_H

#include "IGameObject.h"

class Food : public IGameObject {
    void Update();
    void Draw();
    void PlaceFood();
    void checkCollid();
};
#endif