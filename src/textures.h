#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct Frames {
    SDL_Texture* texture;
    SDL_Rect* frame_rects;
    //location and size of texture
    int current_frame;
    int num_of_frames;

};

struct Floor {
    SDL_Texture* texture;   //texture of the floor
};

struct Texture {
    struct Frames idle;
    struct Frames run;
    struct Frames jump_up;
    struct Frames jump_down;
    //different animation states
    struct Floor floor1;
    struct Floor floor2;
    struct Floor floor3;
    struct Floor floor4;
    //different floor texture
    Uint32 frame_start;
    //the time when the animation started
    float render_speed;
};

class Textures {
public:
    Textures(SDL_Renderer* renderer);// 
    ~Textures();//relese resource when the object is destroyed

    bool load();//loading texture resources
    bool deload();//deload texure resources,

    struct Texture player;//texture resource of the player
    struct Texture tilemap;//texure resourse of the tilemap

private:
    SDL_Renderer* renderer;

    SDL_Texture* load_texture(SDL_Renderer* renderer, const char* file_path);

    const char* PLAYER_IDLE_PATH = "assets/heroes/knight/knight_idle_spritesheet.png";
    const char* PLAYER_RUN_PATH = "assets/heroes/knight/knight_run_spritesheet.png";
    //refer to the spritesheet
    
    const char* TILE_FLOOR_1 = "assets/tiles/floor/floor_1.png";
    const char* TILE_FLOOR_2 = "assets/tiles/floor/floor_2.png";
    const char* TILE_FLOOR_3 = "assets/tiles/floor/floor_3.png";
    const char* TILE_FLOOR_4 = "assets/tiles/floor/floor_4.png";
    //refer to the floor

    const int PLAYER_IDLE_FRAMES = 6;
    const int PLAYER_RUN_FRAMES = 6;

    const float PLAYER_RENDER_SPEED = 1;

    const int PLAYER_WIDTH = 16;
    const int PLAYER_HEIGHT = 16;
    //information of the players
};

#endif // TEXTURES_H
