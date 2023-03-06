#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "game_object/snake.h"

struct sdl_deleter
{
  void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
  void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
  void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
  void operator()(SDL_Surface *p) const { SDL_FreeSurface(p); }
};

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food);
  void UpdateWindowTitle(int score, int fps);

 private:
  bool LoadMedia();

  std::unique_ptr<SDL_Window, sdl_deleter> sdl_window_;
  std::unique_ptr<SDL_Renderer, sdl_deleter> sdl_renderer_;

  //The surface contained by the window
  std::unique_ptr<SDL_Surface, sdl_deleter> sdl_surface_;
  //The image we will load and show on the screen
  std::unique_ptr<SDL_Surface, sdl_deleter> background_img_;
  std::unique_ptr<SDL_Texture, sdl_deleter> background_texure_;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif