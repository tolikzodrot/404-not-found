#include "tilemap.h"

Tilemap::Tilemap(SDL_Renderer* renderer, struct Texture texture, int x, int y, const int SW, const int SH, int MW, int MH):
renderer(renderer), texture(texture), SCREEN_WIDTH(SW), SCREEN_HEIGHT(SH), MAP_WIDTH(MW), MAP_HEIGHT(MH) {
    

    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Define the distribution for integers between 1 and 4
    std::uniform_int_distribution<> distrib(1, 4);

    matrix.resize(MAP_HEIGHT); // Set the number of rows

    // Set the size of each row
    for (int i = 0; i < MAP_HEIGHT; ++i) {
        matrix[i].resize(MAP_WIDTH); // Set the number of columns for each row
    }

    for (int i = 0; i < MAP_HEIGHT; ++i) {
        for (int j = 0; j < MAP_WIDTH; ++j) {
            // You can initialize elements here if needed
            matrix[i][j] = distrib(gen);
        }
    }

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

    for(int x = 0; x < MAP_WIDTH; ++x){
        for(int y = 0; y < MAP_HEIGHT; ++y){
            rect.x = x * WIDTH;
            rect.y = y * HEIGHT;
            switch(matrix[y][x]){
                case 1:
                    render_texture = texture.floor1.texture;
                    break;
                case 2:
                    render_texture = texture.floor2.texture;
                    break;
                case 3:
                    render_texture = texture.floor3.texture;
                    break;
                case 4:
                    render_texture = texture.floor4.texture;
                    break;
            }

            SDL_RenderCopy(renderer, render_texture, NULL, &rect);
        }
    }
}