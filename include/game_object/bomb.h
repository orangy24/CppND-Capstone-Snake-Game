// #ifndef BOMB_H
// #define BOMB_H

// #include "IGameObject.h"

// class Bomb : public IGameObject {
//     void Update();
//     void PlaceFood();
// };
// #endif

// #include <thread>
// #include <future>

// // Define the Bomb class
// class Bomb {
// public:
//     int x, y, size, countdown;
//     bool exploded;

//     Bomb(int _x, int _y) {
//         x = _x;
//         y = _y;
//         size = 10;
//         countdown = 3000; // 3 seconds
//         exploded = false;
//     }

//     void draw(SDL_Renderer* renderer) {
//         SDL_Rect rect = { x - size/2, y - size/2, size, size };
//         SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//         SDL_RenderFillRect(renderer, &rect);
//     }

//     void update(int dt) {
//         countdown -= dt;
//         if (countdown <= 0) {
//             exploded = true;
//         }
//     }

//     bool collidesWithSnake(Snake& snake) {
//         int dx = x - snake.x;
//         int dy = y - snake.y;
//         int distance = std::sqrt(dx*dx + dy*dy);
//         if (distance <= size/2 + snake.size/2) {
//             return true;
//         }
//         return false;
//     }

//     bool collidesWithExplosion(int explosionX, int explosionY, int explosionSize) {
//         int dx = x - explosionX;
//         int dy = y - explosionY;
//         int distance = std::sqrt(dx*dx + dy*dy);
//         if (distance <= size/2 + explosionSize/2) {
//             return true;
//         }
//         return false;
//     }

//     void startTimer() {
//         // Create a promise object to signal when the bomb explodes
//         std::promise<void> promiseObj;

//         // Get the future object from the promise
//         std::future<void> futureObj = promiseObj.get_future();

//         // Create a new thread to run the bomb timer
//         std::thread timerThread(&Bomb::timer, this, std::move(promiseObj));

//         // Detach the thread to run in the background
//         timerThread.detach();

//         // Wait for the timer thread to complete
//         futureObj.get();
//     }

//     void timer(std::promise<void> promiseObj) {
//         while (countdown > 0) {
//             std::this_thread::sleep_for(std::chrono::milliseconds(10));
//             update(10);
//         }

//         // Signal that the bomb has exploded
//         promiseObj.set_value();
//     }
// };

// // In the main game loop:
// std::vector<Bomb> bombs;

// // Spawn a bomb
// Bomb bomb(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
// bombs.push_back(bomb);

// // Draw the bombs
// for (int i = 0; i < bombs.size(); i++) {
//     bombs[i].draw(renderer);
// }

// // Check for collision with the snake
// for (int i = 0; i < bombs.size(); i++) {
//     if (bombs[i].collidesWithSnake(snake)) {
//         bombs[i].startTimer();
//         // The game will continue while the bomb timer runs in a separate thread
//     }
// }

// // When the bomb explodes
// if (bombs[i].exploded) {
//     // Create an explosion effect
//     // ...

//     // Check for collision with the snake
//     if (bombs[i].collidesWithSnake(snake)) {
//         // The snake dies
//         // ...
//     }

//     // Remove the bomb from the list
//     bombs.erase(bombs.begin() + i);
// }

// // When the snake eats a bomb
// if (snake.collides
