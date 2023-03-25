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
          return;
        }
    }
}
void Bomb::Draw(SDL_Renderer* renderer, SDL_Rect& block) {
    // block = { x_ , y_ , size_, size_ };
    block.x = x_ * block.w;
    block.y = y_ * block.h;
    // std::cout<<"draw bomb at"<<block.x<<" "<<block.y<<std::endl;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &block);
}

void Bomb::count_down(int dt) {
    countdown_ -= dt;
    if (countdown_ <= 0) {
        exploded_ = true;
    }
}

bool Bomb::collidesWithSnake() {
    // auto snake
    // int dx = x_ - snake_->x;
    // int dy = y_ - snake_->y;
    // int distance = std::sqrt(dx * dx + dy * dy);
    // if (distance <= size/2 + snake_.size/2) {
    //     return true;
    // }
    return false;
}

bool Bomb::collidesWithExplosion(int explosionX, int explosionY, int explosionSize) {
    int dx = x_ - explosionX;
    int dy = y_ - explosionY;
    int distance = std::sqrt(dx*dx + dy*dy);
    if (distance <= size_/2 + explosionSize/2) {
        return true;
    }
    return false;
}

void Bomb::startTimer() {
    // Create a promise object to signal when the bomb explodes
    std::promise<void> promiseObj;

    // Get the future object from the promise
    std::future<void> futureObj = promiseObj.get_future();

    // Create a new thread to run the bomb timer
    std::thread timerThread(&Bomb::timer, this, std::move(promiseObj));

    // Detach the thread to run in the background
    timerThread.detach();

    // Wait for the timer thread to complete
    futureObj.get();
}

void Bomb::timer(std::promise<void> promiseObj) {
    while (countdown_ > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        count_down(10);
    }

    // Signal that the bomb has exploded
    promiseObj.set_value();
}