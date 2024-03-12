#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct Frames {
    SDL_Texture* texture;
    SDL_Rect* frame_rects;

    int current_frame;
    int num_of_frames;
};

struct Floor {
    SDL_Texture* texture;
};

struct Texture {
    struct Frames idle;
    struct Frames run;
    struct Frames jump_up;
    struct Frames jump_down;
    struct Floor floor;

    Uint32 frame_start;
    float render_speed;
};

class Textures {
public:
    Textures(SDL_Renderer* renderer);
    ~Textures();

    bool load();
    bool deload();

    struct Texture player;
    struct Texture tilemap;

private:
    SDL_Renderer* renderer;

    SDL_Texture* load_texture(SDL_Renderer* renderer, const char* file_path);

    const char* PLAYER_IDLE_PATH = "assets/heroes/knight/knight_idle_spritesheet.png";
    const char* PLAYER_RUN_PATH = "assets/heroes/knight/knight_run_spritesheet.png";
    
    const char* TILE_FLOOR_1 = "assets/tiles/floor/floor_1.png";

    const int PLAYER_IDLE_FRAMES = 6;
    const int PLAYER_RUN_FRAMES = 6;

    const float PLAYER_RENDER_SPEED = 1.5;

    const int PLAYER_WIDTH = 16;
    const int PLAYER_HEIGHT = 16;

};

#endif // TEXTURES_H
