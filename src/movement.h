#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <stdio.h>
#include <vector>
#include <SDL2/SDL.h> // Include SDL_Rect

class Movement {
public:
    Movement(int initialX, int initialY, int initialSpeed, const int screenWidth, const int screenHeight);
    void setSpeed(int newSpeed);
    void set_Collision_Matrix(const std::vector<std::vector<int>>& collisionMatrix);
    void setDirection(int newX, int newY);
    void move(SDL_Rect* actor);
    SDL_Rect* getRect();

private:
    int x;
    int y;
    int speed;
    int dx; // Direction in the x-axis
    int dy; // Direction in the y-axis
    int screenWidth; // Width of the screen
    int screenHeight; // Height of the screen
    std::vector<std::vector<int>> collisionMatrix;
    SDL_Rect rect;

    const int WIDTH = 80;
    const int HEIGHT = 80;

    bool yisWithinScreenBounds(int nextY) const;
    bool xisWithinScreenBounds(int nextX) const;
};

#endif // MOVE_H