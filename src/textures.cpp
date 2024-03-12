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

    return texture;
}

// Load all the textures
bool Textures::load() {

    // Background texture
    //const char* BACKGROUND_PATH = "assets/tiles/floor/spikes_spritesheet.png"; // Adjust the path accordingly
    //backgroundTexture = load_texture(renderer, BACKGROUND_PATH);
    //if (!backgroundTexture) {
    //    return false;
    //}
    
	// Player idle texture
    tilemap.floor.texture = load_texture(renderer, TILE_FLOOR_1);
    if (!tilemap.floor.texture) { return false; }

	player.idle.texture = load_texture(renderer, PLAYER_IDLE_PATH);
	if (!player.idle.texture) { return false; }

	player.idle.frame_rects = new SDL_Rect[PLAYER_IDLE_FRAMES];

    for (int i = 0; i < PLAYER_IDLE_FRAMES; i++) {
        player.idle.frame_rects[i].x = i * PLAYER_WIDTH;
        player.idle.frame_rects[i].y = 0;
        player.idle.frame_rects[i].w = PLAYER_WIDTH;
        player.idle.frame_rects[i].h = PLAYER_HEIGHT;
    }

    player.idle.num_of_frames = PLAYER_IDLE_FRAMES;
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

    player.run.num_of_frames = PLAYER_RUN_FRAMES;
    player.run.current_frame = 1;

    player.frame_start = SDL_GetTicks();
    player.render_speed = PLAYER_RENDER_SPEED;

	return true;
}

// Deload all the textures
bool Textures::deload() {


	// Player texture
    SDL_DestroyTexture(tilemap.floor.texture);
	SDL_DestroyTexture(player.idle.texture);
	delete player.idle.frame_rects;

	return true;
}


