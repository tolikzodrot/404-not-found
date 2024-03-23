#include "movement.h"

Movement::Movement(int initialX, int initialY, int initialSpeed, int screenWidth, int screenHeight)
    : x(initialX), y(initialY), speed(initialSpeed), dx(0), dy(0), screenWidth(screenWidth), screenHeight(screenHeight) {}

void Movement::setSpeed(int newSpeed) {
    speed = newSpeed;
}

void Movement::set_Collision_Matrix(const std::vector<std::vector<int>>& collisionMatrix) {
    this->collisionMatrix = collisionMatrix;
}

void Movement::setDirection(int newX, int newY) {
    dx = newX;
    dy = newY;
}

void Movement::move(SDL_Rect* actor) {
    int moveX = dx;
    int moveY = dy;

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

    while (moveX != 0 || moveY != 0) {
        int nextX = x + (moveX > 0 ? 1 : (moveX < 0 ? -1 : 0));
        int nextY = y + (moveY > 0 ? 1 : (moveY < 0 ? -1 : 0));

        // Check if next position is within screen boundaries
        if (!yisWithinScreenBounds(nextY)){
            nextY = y;
            printf("y is out of bounds\n");
        }
        
        if (!xisWithinScreenBounds(nextX)){
            nextX = x;
            printf("x is out of bounds\n");
        }

        // Create SDL_Rects for the objects
        SDL_Rect playerRect = {x, y, WIDTH, HEIGHT};

        // Check collision with collision matrix
        bool collisionX = false;
        bool collisionY = false;
        for (int i = 0; i < static_cast<int>(collisionMatrix.size()); ++i) {
            for (int j = 0; j < static_cast<int>(collisionMatrix[i].size()); ++j) {
                if (collisionMatrix[i][j] == 1) {
                    SDL_Rect tileRect = {j, i, WIDTH, HEIGHT};
                    playerRect.x = nextX;
                    if (SDL_HasIntersection(&playerRect, &tileRect))
                        collisionX = true;
                    playerRect.y = nextY;
                    playerRect.x = y;
                    if (SDL_HasIntersection(&playerRect, &tileRect))
                        collisionY = true;
                    if (!(collisionX || collisionY)){
                        break;
                    }
                }
            }
        }
        if(!(collisionX))
            x = nextX;
        if(!(collisionY))
            y = nextY;
        
        if (collisionX){
            printf("collision in x\n");
        }else{
            printf("no collision in x\n");
        }
        if (collisionY){
            printf("collision in y\n");
        }else{
            printf("no collision in y\n");
        }
        
        actor->x = x;
        actor->y = y;

        if (moveX > 0) moveX--;
        else if (moveX < 0) moveX++;
        if (moveY > 0) moveY--;
        else if (moveY < 0) moveY++;
    }
}

bool Movement::yisWithinScreenBounds(int nextY) const {
    return nextY >= 0 && nextY < screenHeight-HEIGHT;
}

bool Movement::xisWithinScreenBounds(int nextX) const {
    return nextX >= 0 && nextX < screenWidth-WIDTH;
}