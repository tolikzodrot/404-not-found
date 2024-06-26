#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

struct Frames {
    SDL_Texture* texture;
    SDL_Rect* frame_rects;
    //location and size of texture
    int current_frame;
    int num_of_frames;

};

struct Floor {
    SDL_Texture* texture;   //texture of the floor
    std::vector<std::vector<SDL_Rect>> floor_rects;
};

struct Texture {
    struct Frames idle;
    struct Frames run;
    struct Frames attack;
    struct Frames sword1;
    struct Frames heart;
    //different animation states
    struct Floor floor1;
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
    struct Texture skeleton;//texture resource of the skeleton enemy
    struct Texture boss2;
    struct Texture boss3;

private:
    SDL_Renderer* renderer;

    SDL_Texture* load_texture(SDL_Renderer* renderer, const char* file_path);

    const char* PLAYER_IDLE_PATH = "assets/Character/hero/player_idle_spritesheet.png";
    const char* PLAYER_RUN_PATH = "assets/Character/hero/player_run_spritesheet.png";
    const char* PLAYER_ATTACK_PATH = "assets/Character/hero/player_attack_spritesheet.png";
    const char* SWORD1_PATH = "assets/Character/hero/sword1.png";
    
    const char* SKELETON_IDLE_PATH = "assets/Character/Character_animation/monsters_idle/skeleton1/v2/skeleton1_idle_spritesheet.png";
    const char* BOSS2_IDLE_PATH = "assets/Character/Character_animation/monsters_idle/boss2_idle.png";
    const char* BOSS3_IDLE_PATH = "assets/Character/Character_animation/monsters_idle/boss3_idle.png";

    
    const char* TILE_FLOOR_1 = "assets/tiles/Tileset/Dungeon_Tileset.png";

    const char* HEART = "assets/Character/hero/heart.png";

    const int PLAYER_IDLE_FRAMES = 1;
    const int PLAYER_RUN_FRAMES = 6;
    const int PLAYER_ATTACK_FRAMES = 5;

    const int SKELETON_RENDER_SPEED = 1;
    const int SKELETON_IDLE_FRAMES = 4;

    const int BOSS_IDLE_FRAMES = 6;

    const float PLAYER_RENDER_SPEED = 1;

    const int SKELETON_WIDTH = 16;
    const int SKELETON_HEIGHT = 16;

    const int PLAYER_WIDTH = 16;
    const int PLAYER_HEIGHT = 16;

    const int BOSS2_WIDTH = 24;
    const int BOSS2_HEIGHT = 24;

    const int BOSS3_WIDTH = 36;
    const int BOSS3_HEIGHT = 36;

    const int FLOOR_WIDTH = 16;
    const int FLOOR_HEIGHT = 16;

    const int FLOOR_I = 10;
    const int FLOOR_J = 10;

};

#endif // TEXTURES_H
