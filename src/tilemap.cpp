#include "tilemap.h"

Tilemap::Tilemap(SDL_Renderer* renderer, struct Texture texture, int x, int y, const int SW, const int SH):
renderer(renderer), texture(texture), SCREEN_WIDTH(SW), SCREEN_HEIGHT(SH) {
    rect.x = x;
    rect.y = y;
    rect.w = WIDTH;
    rect.h = HEIGHT;
}

Tilemap::~Tilemap() {
}

void Tilemap::update() {
}

void Tilemap::render() {
    SDL_Texture* render_texture;

    render_texture = texture.floor.texture;
    for(int x = 0; x < MAP_WIDTH; ++x){
        for(int y = 0; y < MAP_WIDTH; ++y){
            rect.x = x * WIDTH;
            rect.y = y * HEIGHT;
            SDL_RenderCopy(renderer, render_texture, NULL, &rect);
        }
    }
}