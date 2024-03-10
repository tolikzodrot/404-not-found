#include "game.h"

Game::Game() {
}

Game::~Game() {
    // Deload all the textures
    textures->deload();
    delete textures;

    // Delete the player
    delete player;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

bool Game::init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }


    // Initialize SDL_image
    if (!(IMG_Init(IMG_INIT_TIF) & IMG_INIT_TIF)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return 1;
    }

    // Get the display mode of the primary monitor
    SDL_DisplayMode display_mode;
    if (SDL_GetCurrentDisplayMode(0, &display_mode) != 0) {
        // Handle getting display mode error
        printf("SDL could not get display dimensions! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    SCREEN_WIDTH = display_mode.w;
    SCREEN_HEIGHT = display_mode.h;
    SCREEN_WIDTH = 1200;
    SCREEN_HEIGHT = 500;

    // Create the windows using the monitors dimensions (fullscreen) FOR RELEASE: SDL_WINDOW_FULLSCREEN
    window = SDL_CreateWindow("The Depth of Eternity", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Create the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Load all the textures (exit if there is an error loading a texture)
    textures = new Textures(renderer);
    if (!textures->load()) {
        running = false;
    }

    // Disable the cursor
    SDL_ShowCursor(SDL_DISABLE);

    // Initialize the player object (with starting position)
    player = new Player(renderer, textures->player, 100, SCREEN_HEIGHT - 100, FPS, SCREEN_WIDTH, SCREEN_HEIGHT);

    return true;
}

void Game::run() {
    // Initialize the FPS handlers
    Uint32 frame_start;
    int frame_time;

    while (running) {
        // Get the current time
        frame_start = SDL_GetTicks();

        // Handle the input
        input();

        // Update the game logic
        update();
        // Render
        render();

        // Control the frame rate
        frame_time = SDL_GetTicks() - frame_start;
        if (1000 / FPS > frame_time) {
            SDL_Delay(1000 / FPS - frame_time);
        }
    }
}

void Game::input() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
    	// If quit is detected
        if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q))) {
            // Quit the game
            running = false;
        }

        // Handle the input for the player
        player->handle_input(event);
    }
}

void Game::update() {
    // Update the player
    player->update();
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // TEST FOR HITBOXES
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Render the player object
    player->render();

    SDL_RenderPresent(renderer);
}
