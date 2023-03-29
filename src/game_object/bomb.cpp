#include "game_object/bomb.h"


void Bomb::Spawn(Snake* snake) {
    int x, y;
    while (true) {
        x = random_w(engine);
        y = random_h(engine);
        // Check that the location is not occupied by a snake item before placing
        // food.
        if (!snake->SnakeCell(x, y)) {
          this->x_ = x;
          this->y_ = y;
          std::cout<<"create a bomb at"<<x<<" "<<y<<std::endl;
          startTimer(3);
          return;
        }
    }
}
void Bomb::Draw(SDL_Renderer* renderer, SDL_Rect& block) {
    // block = { x_ , y_ , size_, size_ };
    block.x = x_ * block.w;
    block.y = y_ * block.h;
    // std::cout<<"draw bomb at"<<block.x<<" "<<block.y<<std::endl;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &block);
}
bool Bomb::CoolDown() {
    uint32_t currentTick = SDL_GetTicks();
    uint32_t duration = currentTick - explode_time_;
    if (duration > exlode_duration_ && exploding_) {
        return true;
    }
    return false;
}
void Bomb::DrawExplode(SDL_Renderer* renderer, SDL_Rect& block) {
    // block = { x_ , y_ , size_, size_ };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // explode at x, y
    // x - 2, y
    SDL_Rect rectX = {
        x_ * block.w -  block.w * EXPLODERAD,
        y_ * block.h ,
        block.w * (2 * EXPLODERAD + 1) ,
        block.h
    };
    SDL_RenderDrawRect(renderer, &rectX);
    SDL_Rect rectY = {
        x_ * block.w ,
        y_ * block.h - EXPLODERAD * block.h ,
        block.w ,
        block.h * (2 * EXPLODERAD + 1)
    };
    SDL_RenderDrawRect(renderer, &rectY);
        // SDL_RenderFillRect(renderer, &rect);
}

void Bomb::count_down(int dt) {
    countdown_ -= dt;
    if (countdown_ <= 0) {
        std::cout<<"exploded"<<std::endl;
        exploding_ = true;
        explode_time_ = SDL_GetTicks();
    }
}

bool Bomb::collidesWithExplosion(Snake* snake) {
    for (int i = -EXPLODERAD; i <= EXPLODERAD; i++) {
        if(snake->SnakeCell(x_ + i, y_) || snake->SnakeCell(x_, y_ + i)) return true;
    }
    return false;
}

bool Bomb::collidesWithoutExplosion(Snake* snake) {
    if(snake->SnakeCell(x_, y_)) {
        return true;
    }
    return false;
}

void Bomb::startTimer(int sec) {
    // Create a promise object to signal when the bomb explodes
    std::promise<void> promiseObj;
    countdown_ = sec * 1000;
    exploding_ = false;
    // Get the future object from the promise
    futureObj_ = promiseObj.get_future();

    // Create a new thread to run the bomb timer
    std::thread timerThread(&Bomb::timer, this, std::move(promiseObj));

    // Detach the thread to run in the background
    timerThread.detach();

}

void Bomb::timer(std::promise<void> promiseObj) {
    while (countdown_ > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        count_down(10);
    }

    // Signal that the bomb has exploded
    promiseObj.set_value();
}