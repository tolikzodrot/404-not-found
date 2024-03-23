#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "textures.h"
#include "player.h"
#include "tilemap.h"
#include "movement.h"

class Game {
public:
    Game();
    ~Game();

    bool init();//initialize the function
    void run();//run the game

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    Textures* textures = nullptr;

    const float FPS = 60.0;//define the game's target frame rate
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;//the width and height of the screen

    int MAP_WIDTH = 15;
    int MAP_HEIGHT = 6;//the width and height of the map

    bool running = true;

    Player* player = nullptr;
    Tilemap* tilemap = nullptr;

    void input();//processing game input
    void update();//uptate the game
    void render();//render game screen
};

#endif // GAME.H
