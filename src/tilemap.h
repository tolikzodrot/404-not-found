#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>//vector containers are introduced to store data
#include <random>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "textures.h"



class Tilemap {
public:
    Tilemap(SDL_Renderer* renderer, struct Texture texture, const int x, const int y, 
    //const int SW, const int SH, 
    int MW, int MH);
    ~Tilemap();
    //build a function to initialize tilemap
    void update();
    void render();
    void setcollisionmatrix();
    void updateEnemies(int i);
    int room = 1;
    int enemies = 1;

    std::vector<std::vector<int>> collision_matrix;

private:
    std::vector<std::vector<int>> room1 = {
        {6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 8},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 10},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9}};
    
    std::vector<std::vector<int>> room2 = {
        {6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 8},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {11, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 10},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9}};

    std::vector<std::vector<int>> room3 = {
        {6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 8},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {11, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9}};
    SDL_Renderer* renderer;
    SDL_Rect rect;

    // Create an empty 2D vector
    std::vector<std::vector<int>> matrix;
    //a two-dimensional vector used to store tile data for the map
    
    //const int SCREEN_WIDTH;
    //const int SCREEN_HEIGHT;


    const int WIDTH = 80;
    const int HEIGHT = 80;

    
    SDL_Rect left_door = {14*WIDTH, 6*HEIGHT, WIDTH, HEIGHT};
    SDL_Rect right_door = {0, 6*HEIGHT, WIDTH, HEIGHT};

    

    int MAP_WIDTH;
    int MAP_HEIGHT;
    
    struct Texture texture;
    //information about the tile
    
};

#endif // TILEMAP_H