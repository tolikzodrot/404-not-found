#include "tilemap.h"
// This is the implementation file for the Tilemap class.
// It defines the member functions of the class.

#include "tilemap.h"

// Constructor for the Tilemap class
// Initializes the renderer, texture, position, and size of the tilemap
Tilemap::Tilemap(SDL_Renderer* renderer, struct Texture texture, int x, int y, int MW, int MH):
    renderer(renderer), texture(texture), MAP_WIDTH(MW), MAP_HEIGHT(MH) {
    
    // Resize the matrix and collision_matrix vectors based on the map dimensions
    matrix.resize(MAP_HEIGHT);
    collision_matrix.resize(MAP_HEIGHT);
    for (int i = 0; i < MAP_HEIGHT; ++i) {
        matrix[i].resize(MAP_WIDTH);
        collision_matrix[i].resize(MAP_WIDTH);
    }

    // Set the values of the matrix
    std::vector<std::vector<int>> new_values = {
        {6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 8},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 10},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7},
        {3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9}};
    matrix = new_values;

    // Set the position and size of the tilemap rectangle
    rect.x = x;
    rect.y = y;
    rect.w = WIDTH;
    rect.h = HEIGHT;
}

// Destructor for the Tilemap class
Tilemap::~Tilemap() {
}

// Sets the collision matrix for the tilemap
void Tilemap::setcollisionmatrix(){
    // Set all elements of the collision matrix to 0
    for(int i = 0; i < MAP_HEIGHT; ++i){
        for(int j = 0; j < MAP_WIDTH; ++j){
            collision_matrix[i][j] = 0;
        }
    }

    // Set the boundary elements of the collision matrix to 1
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
}

// Updates the tilemap
void Tilemap::update() {
    if(room == 1){
        matrix = room1;
        if(enemies == 0){
            collision_matrix[4][14] = 0;
        }else{
            collision_matrix[4][14] = 1;
        }
    }else if(room > 1 && room < 5){
        matrix = room2;
        if(enemies == 0){
            collision_matrix[4][0] = 0;
            collision_matrix[4][14] = 0;
        }else{
            collision_matrix[4][0] = 1;
            collision_matrix[4][14] = 1;
        }
    }else if(room == 5){
        matrix = room3;
        if(enemies == 0){
            collision_matrix[4][0] = 0;
        }else{
            collision_matrix[4][0] = 1;
        }
    }

    for(int i = 0; i < MAP_HEIGHT; ++i){
        for(int j = 0; j < MAP_WIDTH; ++j){
            printf("%d ", collision_matrix[i][j]);
        }
        printf("\n");
    }
}

// Renders the tilemap
void Tilemap::render() {
    SDL_Texture* render_texture;
    SDL_Rect* render_rect;

    // Render each tile in the tilemap
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
                case 10:
                    render_texture = texture.floor1.texture;
                    render_rect = &texture.floor1.floor_rects[5][0];
                    break;
                case 11:
                    render_texture = texture.floor1.texture;
                    render_rect = &texture.floor1.floor_rects[5][3];
                    break;
            }
            SDL_RenderCopy(renderer, render_texture, render_rect, &rect);
        }
    }
    SDL_Rect doorRect = {14*80, 4*80, 80, 80};
    if(enemies != 0){
        SDL_RenderCopy(renderer, render_texture, &texture.floor1.floor_rects[5][7], &doorRect);
    }
}

void Tilemap::updateEnemies(int i){
    enemies = i;
}