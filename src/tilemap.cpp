#include "tilemap.h"

Tilemap::Tilemap(SDL_Renderer* renderer, struct Texture texture, int x, int y, 
//const int SW, const int SH, 
int MW, int MH):
renderer(renderer), texture(texture), 
//SCREEN_WIDTH(SW), SCREEN_HEIGHT(SH), 
MAP_WIDTH(MW), MAP_HEIGHT(MH) {
    

    // Seed the random number generator
    //std::random_device rd;
    //std::mt19937 gen(rd());
    
    // Define the distribution for integers between 1 and 4
    //std::uniform_int_distribution<> distrib(1, 4);

    matrix.resize(MAP_HEIGHT); // Set the number of rows
    collision_matrix.resize(MAP_HEIGHT);

    // Set the size of each row
    for (int i = 0; i < MAP_HEIGHT; ++i) {
        matrix[i].resize(MAP_WIDTH); // Set the number of columns for each row
        collision_matrix[i].resize(MAP_WIDTH);
    }

    std::vector<std::vector<int>> new_values = {
        {6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 8},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9}};
    matrix = new_values;


    rect.x = x;
    rect.y = y;
    rect.w = WIDTH;
    rect.h = HEIGHT;
    //to locate and draw tiles in the screen
}

Tilemap::~Tilemap() {
}

void Tilemap::setcollisionmatrix(){
    for(int i = 0; i < MAP_HEIGHT; ++i){
        for(int j = 0; j < MAP_WIDTH; ++j){
            collision_matrix[i][j] = 0;
        }
    }
    for(int i = 0; i < MAP_HEIGHT; ++i){
        collision_matrix[i][0] = 1;
    }
    for(int i = 0; i < MAP_WIDTH; ++i){
        collision_matrix[0][i] = 1;
    }
    for(int i = 0; i < MAP_HEIGHT; ++i){
        collision_matrix[i][MAP_WIDTH-1] = 1;
    }
    for(int i = 0; i < MAP_WIDTH; ++i){
        collision_matrix[MAP_HEIGHT-1][i] = 1;
    }
    collision_matrix[MAP_HEIGHT-4][MAP_WIDTH-4] = 1;
    for(int i = 0; i < MAP_HEIGHT; ++i){
        for(int j = 0; j < MAP_WIDTH; ++j){
            printf("%d ", collision_matrix[i][j]);
        }
        printf("\n");
    }
    
    
}

void Tilemap::update() {
}

void Tilemap::render() {
    SDL_Texture* render_texture;
    SDL_Rect* render_rect;

    for(int x = 0; x < MAP_WIDTH; ++x){
        for(int y = 0; y < MAP_HEIGHT; ++y){
            rect.x = x * WIDTH;
            rect.y = y * HEIGHT;
            switch(matrix[y][x]){
                case 1:
                    render_texture = texture.floor1.texture;
                    render_rect = &texture.floor1.floor_rects[2][2];
                    break;
                case 2:
                    render_texture = texture.floor1.texture;
                    render_rect = &texture.floor1.floor_rects[4][1];
                    break;
                case 3:
                    render_texture = texture.floor1.texture;
                    render_rect = &texture.floor1.floor_rects[4][0];
                    break;
                case 4:
                    render_texture = texture.floor1.texture;
                    render_rect = &texture.floor1.floor_rects[1][0];
                    break;
                case 5:
                    render_texture = texture.floor1.texture;
                    render_rect = &texture.floor1.floor_rects[0][2];
                    break;
                case 6:
                    render_texture = texture.floor1.texture;
                    render_rect = &texture.floor1.floor_rects[0][0];
                    break;
                case 7:
                    render_texture = texture.floor1.texture;
                    render_rect = &texture.floor1.floor_rects[1][5];
                    break;
                case 8:
                    render_texture = texture.floor1.texture;
                    render_rect = &texture.floor1.floor_rects[0][5];
                    break;
                case 9:
                    render_texture = texture.floor1.texture;
                    render_rect = &texture.floor1.floor_rects[4][5];
                    break;
            }
            //select the corresponding texture
            SDL_RenderCopy(renderer, render_texture, render_rect, &rect);
        }
    }
}