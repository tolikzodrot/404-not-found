#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>

#include "movement.h"
#include "tilemap.h"
#include "textures.h"

//different states of the player
class Player {
public:
    Player(SDL_Renderer* renderer, struct Texture texture, const int x, const int y, const float FPS, const int SW, const int SH);
    //build function to initialize the player
    ~Player();
    //to clean up player objects
    
    void isHit(SDL_Rect enemy);
    void handle_input(SDL_Event event);//handle game input events,like keystokens mouse movements
    void update();//update the player's state
    void render();//render the player onto the screen
    SDL_Rect getSwordRect();
    SDL_Rect getRect();
    
    SDL_Rect rect;//to describe the location and size of the player

    

    Movement movement;

private:
    struct Kickback
    {
        double x;
        double y;
    };
    

    SDL_Rect calculateRectWithAngle(const SDL_Rect& originalRect, double angle, double radius);
    
    enum Player_State {
        IDLE,
        RUN,
        ATTACK,
        DEAD
    };
    
    enum Attack_State {
        SWING,
        HALT
    };

    SDL_Renderer* renderer;
    
    SDL_Rect sword_rect;//to describe the location and size of the sword

    SDL_Rect sword_rect_rotated;

    Kickback kickback = {0, 0};
    

    Player_State state = IDLE;
    Player_State attack = IDLE;
    Attack_State attackState = HALT;

    int HP = 10;

    SDL_Point center;

    const float initialSwordRotation = 300.0f;
    float swordRotation;

    Uint32 start_time_degree;
    Uint32 start_time_swing = 0;
    Uint32 invinsibility = 0;

    const float FPS;//frequency of the game
    //width,height of the screen
    const int WIDTH = 80;
    const int HEIGHT = 80;
    const int SWORD_WIDTH = 80;
    const int SWORD_HEIGHT = 80;

    int direction_X = 0;
    int direction_Y = 0;

    float speed = FPS * 10.0;
    //width,height,direction,speed of the player
    struct Texture texture;
    int looking_direction = 1;
    //set the face direction,left or right
    //information of the player
    void collision_visual();
};

#endif // PLAYER_H
