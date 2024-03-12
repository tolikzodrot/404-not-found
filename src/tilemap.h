#ifndef TILEMAP_H
#define TILEMAP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "textures.h"

class Tilemap {
public:
    Tilemap(SDL_Renderer* renderer, struct Texture texture, const int x, const int y, const int SW, const int SH);
    ~Tilemap();

    void update();
    void render();

private:
    SDL_Renderer* renderer;
    SDL_Rect rect;

    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;

    const int WIDTH = 80;
    const int HEIGHT = 80;

    const int MAP_WIDTH = 15;
    const int MAP_HEIGHT = 6;
    
    struct Texture texture;
    
};

#endif // PLAYER_H