#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>  
#include <string>

#include "textures.h"
#include "player.h"
#include "tilemap.h"
#include "movement.h"
#include "enemy.h"

enum Gamestate{
    MENU,
    LOADING,
    PLAYING
};

class Game {
public:
    Game();
    ~Game();

    bool init();//initialize the function
    void run();//run the game
    bool isMouseInButton(SDL_Event* event, int x, int y, int w, int h) ; 
    bool isRunning() const;
    void handleMenuInput();
    bool loadMedia(SDL_Renderer* renderer);


private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Textures* textures = nullptr;
    SDL_Texture* menuBackground=nullptr;

    const float FPS = 60.0;//define the game's target frame rate
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;//the width and height of the screen
    const char* menuBackgroundPath= "assets/tiles/menu/menuBackgroundPath.png";

    const int  BUTTON_PLAY_X = 850;
    const int BUTTON_PLAY_Y = 430;
    const int  BUTTON_PLAY_W = 430;
    const int BUTTON_PLAY_H = 105;
    const int BUTTON_LOAD_X = 695;
    const int BUTTON_LOAD_Y = 565;
    const int  BUTTON_LOAD_W = 230 ;
    const int  BUTTON_LOAD_H = 120;
    const int BUTTON_EXIT_X = 955;
    const int BUTTON_EXIT_Y = 565;
    const int BUTTON_EXIT_W = 230;
    const int BUTTON_EXIT_H = 120;

    int MAP_WIDTH;
    int MAP_HEIGHT;//the width and height of the map

    int room = 0;

    bool running = true;
    bool  Gamestate = MENU;
    Player* player = nullptr;
    Tilemap* tilemap = nullptr;
    Enemy* skeleton = nullptr;
    Enemy* boss2 = nullptr;
    Enemy* boss3 = nullptr;

    void input();//processing game input
    void update();//uptate the game
    void render();//render game screen
};

#endif // GAME.H