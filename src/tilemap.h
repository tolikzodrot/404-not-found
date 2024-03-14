#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <random>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "textures.h"

class Tilemap {
public:
    Tilemap(SDL_Renderer* renderer, struct Texture texture, const int x, const int y, const int SW, const int SH, int MW, int MH);
    ~Tilemap();

    void update();
    void render();

private:
    SDL_Renderer* renderer;
    SDL_Rect rect;

    // Create an empty 2D vector
    std::vector<std::vector<int>> matrix;

    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;

    const int WIDTH = 80;
    const int HEIGHT = 80;

    int MAP_WIDTH;
    int MAP_HEIGHT;
    
    struct Texture texture;
    
};

#endif // PLAYER_H