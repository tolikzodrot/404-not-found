#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "movement.h"
#include "tilemap.h"
#include "textures.h"

class Enemy {
public:
    Enemy(SDL_Renderer* renderer, struct Texture texture, const int x, const int y, const float FPS, const int SW, const int SH);
    //build function to initialize the enemy
    ~Enemy();
    //to clean up enemy objects
    void update();//update the enemy's state
    void render();//render the enemy onto the screen
    void isHit(SDL_Rect sword);//check if the enemy is hit
    int check_state();//check if enemy is dead
    void targetUpdate(SDL_Rect rect);
    void setState();
    void setPos(int x, int y);

    SDL_Rect rect;//to describe the location and size of the enemy

    Movement movement;

private:
    enum Enemy_State {
        IDLE,
        RUN,
        ATTACK,
        DEAD
    };

    Uint32 halt = 0;
    SDL_Renderer* renderer;
    SDL_Rect target;

    Enemy_State state = IDLE;

    const float FPS;//frequency of the game
    //width,height of the screen
    const int WIDTH = 80;
    const int HEIGHT = 80;
    int direction_X = 0;
    int direction_Y = 0;
    float speed = FPS * 5.0;
    //width,height,direction,speed of the enemy
    struct Texture texture;
    int looking_direction = 1;
    //set the face direction,left or right
    //information of the enemy
};

#endif // ENEMY_H
