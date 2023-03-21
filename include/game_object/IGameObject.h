#ifndef I_GAME_OBJECT_H
#define I_GAME_OBJECT_H
#include "SDL.h"

class IGameObject {
    virtual void Update() = 0;
    virtual void Draw(SDL_Renderer* sdl_renderer, SDL_Rect& block) = 0;
};
#endif