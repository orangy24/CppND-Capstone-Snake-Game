#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height),
      sdl_window_(nullptr, sdl_deleter()),
      sdl_renderer_(nullptr, sdl_deleter()) {

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create Window
    sdl_window_.reset(SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, screen_width,
                                  screen_height, SDL_WINDOW_SHOWN));

    if (nullptr == sdl_window_.get()) {
        std::cerr << "Window could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create renderer
    sdl_renderer_.reset(SDL_CreateRenderer(sdl_window_.get(), -1, SDL_RENDERER_ACCELERATED));
    if (nullptr == sdl_renderer_.get()) {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
    if (!LoadMedia()) {
        std::cout<<"load image fail"<<std::endl;
        std::cerr << "fail to load image. \n";
    } else {
        std::cout<<"load image"<<std::endl;
        background_texure_.reset(SDL_CreateTextureFromSurface(sdl_renderer_.get(), background_img_.get()));
    }

}

Renderer::~Renderer() {
    SDL_Quit();
}

bool Renderer::LoadMedia() {
    bool success = true;
    background_img_.reset(SDL_LoadBMP("../background.bmp"));
    if (background_img_.get() == nullptr) {
        std::cout<<"load media fail"<<std::endl;
        std::cerr << "image could not be loaded. SDL_Error: " << SDL_GetError() << "\n";
        success = false;
    }
    return success;
}
void Renderer::Render(Snake* snake_ptr, Food* food_ptr, std::vector<std::shared_ptr<Bomb>> bombs) {
    SDL_Rect block;
    block.w = screen_width / grid_width;
    block.h = screen_height / grid_height;

    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer_.get(), 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer_.get());
    RenderBackground();

    // Render food
    food_ptr->Draw(sdl_renderer_.get(), block);

    // Render snake
    snake_ptr->Draw(sdl_renderer_.get(), block);

    //Render Bomb
    for (const auto& bomb : bombs) {
        bomb->Draw(sdl_renderer_.get(), block);
    }
    // Update Screen
    SDL_RenderPresent(sdl_renderer_.get());
}

void Renderer::RenderBackground() {
    //render background
    SDL_RenderCopy(sdl_renderer_.get(), background_texure_.get(), NULL, NULL);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window_.get(), title.c_str());
}
