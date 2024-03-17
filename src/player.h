#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "textures.h"

enum Player_State {
    IDLE,
    RUN,
    JUMP_UP,
    JUMP_DOWN,
};
//different states of the player
class Player {
public:
    Player(SDL_Renderer* renderer, struct Texture texture, const int x, const int y, const float FPS, const int SW, const int SH);
    //build function to initialize the player
    ~Player();
    //to clean up player objects
    void handle_input(SDL_Event event);//handle game input events,like keystokens mouse movements
    void update();//update the player's state
    void render();//render the player onto the screen

private:
    SDL_Renderer* renderer;
    SDL_Rect rect;//to describe the location and size of the player

    Player_State state = IDLE;

    const float FPS;//frequency of the game
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;
    //width,height of the screen
    const int WIDTH = 80;
    const int HEIGHT = 80;
    int direction_X = 0;
    int direction_Y = 0;
    float speed = FPS * 10.0;
    //width,height,direction,speed of the player
    struct Texture texture;
    int looking_direction = 1;
    //set the face direction,left or right
    //information of the player
};

#endif // PLAYER_H
