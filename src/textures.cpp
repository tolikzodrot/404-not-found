#include "textures.h"

Textures::Textures(SDL_Renderer* renderer) : renderer(renderer) {
}

Textures::~Textures() {
}

// Loads and returns a texture using the renderer from the given file path
SDL_Texture* Textures::load_texture(SDL_Renderer* renderer, const char* file_path) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, file_path);
    if (!texture) {
        printf("Unable to load texture from %s! SDL Error: %s\n", file_path, SDL_GetError());
        return nullptr;
    }
    tilemap.floor1.floor_rects.resize(FLOOR_I);
    for (int i = 0; i < FLOOR_I; i++) {
        tilemap.floor1.floor_rects[i].resize(FLOOR_J);
    }

    return texture;
}


// Load all the textures and initialize the player animations 
// Returns true if all textures are loaded successfully, false otherwise
bool Textures::load() {
    
	skeleton.idle.num_of_frames = SKELETON_IDLE_FRAMES;
    skeleton.idle.current_frame = 1;
    skeleton.render_speed = SKELETON_RENDER_SPEED;
    skeleton.idle.texture = load_texture(renderer, SKELETON_IDLE_PATH);
    if (!skeleton.idle.texture) { return false; }

    skeleton.idle.frame_rects = new SDL_Rect[SKELETON_IDLE_FRAMES];
    for (int i = 0; i < SKELETON_IDLE_FRAMES; i++) {
        skeleton.idle.frame_rects[i].x = i * SKELETON_WIDTH;
        skeleton.idle.frame_rects[i].y = 0;
        skeleton.idle.frame_rects[i].w = SKELETON_WIDTH;
        skeleton.idle.frame_rects[i].h = SKELETON_HEIGHT;
    }

    tilemap.floor1.texture = load_texture(renderer, TILE_FLOOR_1);
    if (!tilemap.floor1.texture) { return false; }
	
    for(int i = 0; i < FLOOR_I; i++){
        for(int j = 0; j < FLOOR_J; j++){
            tilemap.floor1.floor_rects[i][j].x = j * FLOOR_WIDTH;
            tilemap.floor1.floor_rects[i][j].y = i * FLOOR_HEIGHT;
            tilemap.floor1.floor_rects[i][j].w = FLOOR_WIDTH;
            tilemap.floor1.floor_rects[i][j].h = FLOOR_HEIGHT;
        }
    }

    player.attack.texture = load_texture(renderer, PLAYER_ATTACK_PATH);
    if (!player.attack.texture) { return false; }
    player.attack.frame_rects = new SDL_Rect[PLAYER_ATTACK_FRAMES];
    for (int i = 0; i < PLAYER_ATTACK_FRAMES; i++) {
        player.attack.frame_rects[i].x = i * PLAYER_WIDTH;
        player.attack.frame_rects[i].y = 0;
        player.attack.frame_rects[i].w = PLAYER_WIDTH;
        player.attack.frame_rects[i].h = PLAYER_HEIGHT;
    }
    player.attack.num_of_frames = PLAYER_ATTACK_FRAMES;
    player.attack.current_frame = 1;

    player.idle.texture = load_texture(renderer, PLAYER_IDLE_PATH);
	if (!player.idle.texture) { return false; }
	player.idle.frame_rects = new SDL_Rect[PLAYER_IDLE_FRAMES];
    for (int i = 0; i < PLAYER_IDLE_FRAMES; i++) {
        player.idle.frame_rects[i].x = i * PLAYER_WIDTH;
        player.idle.frame_rects[i].y = 0;
        player.idle.frame_rects[i].w = PLAYER_WIDTH;
        player.idle.frame_rects[i].h = PLAYER_HEIGHT;
    }
    //load the texture of idle state player
    player.idle.num_of_frames = PLAYER_IDLE_FRAMES;//total number of idle state animation frames
    player.idle.current_frame = 1;

    // Player run texture
	player.run.texture = load_texture(renderer, PLAYER_RUN_PATH);
	if (!player.run.texture) { return false; }
	player.run.frame_rects = new SDL_Rect[PLAYER_RUN_FRAMES];
    for (int i = 0; i < PLAYER_RUN_FRAMES; i++) {
        player.run.frame_rects[i].x = i * PLAYER_WIDTH;
        player.run.frame_rects[i].y = 0;
        player.run.frame_rects[i].w = PLAYER_WIDTH;
        player.run.frame_rects[i].h = PLAYER_HEIGHT;
    }
    //load the taxture of running state player
    player.run.num_of_frames = PLAYER_RUN_FRAMES;//total number of the running state animation frame
    player.run.current_frame = 1;

    player.frame_start = SDL_GetTicks();//get the current system time
    player.render_speed = PLAYER_RENDER_SPEED;

    player.sword1.texture = load_texture(renderer, SWORD1_PATH);
    if (!player.sword1.texture) { return false; }

    player.heart.texture = load_texture(renderer, HEART);
    if (!player.heart.texture) { return false; }

	return true;
}

// Deload all the textures
bool Textures::deload() {

    //destroy the texture of the player
    SDL_DestroyTexture(tilemap.floor1.texture);
	SDL_DestroyTexture(player.idle.texture);
    SDL_DestroyTexture(player.run.texture);
    SDL_DestroyTexture(player.attack.texture);
    SDL_DestroyTexture(skeleton.idle.texture);
    SDL_DestroyTexture(player.sword1.texture);

    //destroy all the objects,release memory
	return true;
}


