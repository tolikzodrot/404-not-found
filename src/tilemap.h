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

    std::vector<std::vector<int>> collision_matrix;

private:
    SDL_Renderer* renderer;
    SDL_Rect rect;

    // Create an empty 2D vector
    std::vector<std::vector<int>> matrix;
    //a two-dimensional vector used to store tile data for the map
    
    //const int SCREEN_WIDTH;
    //const int SCREEN_HEIGHT;

    const int WIDTH = 80;
    const int HEIGHT = 80;

    int MAP_WIDTH;
    int MAP_HEIGHT;
    
    struct Texture texture;
    //information about the tile
    
};

#endif // TILEMAP_H