#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "textures.h"
#include "player.h"

class Game {
public:
    Game();
    ~Game();

    bool init();
    void run();

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    Textures* textures = nullptr;

    const float FPS = 60.0;
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;

    bool running = true;

    Player* player = nullptr;

    void input();
    void update();
    void render();
};

#endif // GAME.H
