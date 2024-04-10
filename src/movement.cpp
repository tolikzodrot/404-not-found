#include "movement.h"

Movement::Movement( int initialSpeed, int screenWidth, int screenHeight)
    : speed(initialSpeed), dx(0), dy(0), screenWidth(screenWidth), screenHeight(screenHeight) {
    // Constructor for the Movement class. Initializes the member variables.
}

void Movement::setSpeed(int newSpeed) {
    speed = newSpeed;
    // Sets the speed of the movement.
}

void Movement::set_Collision_Matrix(const std::vector<std::vector<int>>& collisionMatrix) {
    this->collisionMatrix = collisionMatrix;
    // Sets the collision matrix used for collision detection.
}

void Movement::setDirection(int newX, int newY) {
    dx = newX;
    dy = newY;
    // Sets the direction of movement.
}

void Movement::move(SDL_Rect* actor, int setting, int moveX, int moveY){
    x = actor->x + 20;
    y = actor->y + 20;

    if (setting == 0){
        moveX = dx;
        moveY = dy;

        if(dx > 0){
            moveX = speed;
        }else if(dx < 0)
            moveX = -1 * speed;

        if(dy > 0){
            moveY = speed;
        }else if(dy < 0)
            moveY = -1 * speed;

        if(dy != 0 && dx != 0){
            moveX = moveX * 0.7072;
            moveY = moveY * 0.7072;
        }
    }

    //printf("moveX: %d, moveY: %d\n", moveX, moveY);

    while (moveX != 0 || moveY != 0) {
        int nextX = x + (moveX > 0 ? 1 : (moveX < 0 ? -1 : 0));
        int nextY = y + (moveY > 0 ? 1 : (moveY < 0 ? -1 : 0));

        // Check if next position is within screen boundaries
        if (!yisWithinScreenBounds(nextY)){
            nextY = y;
        }
        if (!xisWithinScreenBounds(nextX)){
            nextX = x;
        }
        
        SDL_Rect playerRect = {x, y, PLAYERWIDTH, PLAYERHEIGHT};

        // Check collision with collision matrix
        bool collisionX = false;
        bool collisionY = false;
        for (int i = 0; i < static_cast<int>(collisionMatrix.size()); ++i) {
            for (int j = 0; j < static_cast<int>(collisionMatrix[i].size()); ++j) {
                if (collisionMatrix[i][j] == 1) {
                    SDL_Rect tileRect = {j*WIDTH, i*HEIGHT, WIDTH, HEIGHT};
                    playerRect.y = y;
                    playerRect.x = nextX;
                    
                    if (SDL_HasIntersection(&playerRect, &tileRect)){
                        collisionX = true;
                        //rect = tileRect;
                    }

                    playerRect.y = nextY;
                    playerRect.x = x;

                    if (SDL_HasIntersection(&playerRect, &tileRect)){
                        collisionY = true;
                        //rect = tileRect;
                    }
                }
            }
        }
        if(!(collisionX))
            x = nextX;
        
        if(!(collisionY))
            y = nextY;

        if (moveX > 0) moveX--;
        else if (moveX < 0) moveX++;
        if (moveY > 0) moveY--;
        else if (moveY < 0) moveY++;
    }
    actor->x = x-20;
    actor->y = y-20;
    // Moves the actor based on the current direction and speed, taking into account collision detection.
}

bool Movement::yisWithinScreenBounds(int nextY) const {
    return nextY >= 0 && nextY < screenHeight-PLAYERHEIGHT;
    // Checks if the next Y position is within the screen boundaries.
}

bool Movement::xisWithinScreenBounds(int nextX) const {
    return nextX >= 0 && nextX < screenWidth-PLAYERWIDTH;
    // Checks if the next X position is within the screen boundaries.
}

SDL_Rect* Movement::getRect() {
    return &rect;
}