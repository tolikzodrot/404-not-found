#include "game.h"
SDL_Texture* menuBackground=nullptr;
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
    SDL_DestroyTexture(menuBackground); 
    SDL_Quit();
    IMG_Quit();
}

bool Game::loadMedia(SDL_Renderer* renderer) {  
    const char* menuBackgroundPath= "assets/tiles/menu/menuBackgroundPath.png";
    menuBackground = IMG_LoadTexture(renderer, menuBackgroundPath);  
    if (menuBackground == NULL) {  
        printf("Failed to load media!\n");  
        return false;  
    }  
  
    return true;  
}  

bool Game::init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    if (!(IMG_Init(IMG_INIT_TIF) & IMG_INIT_TIF)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        SDL_Quit();
        return false;
    }

    // Get the display mode of the primary monitor
    SDL_DisplayMode display_mode;
    if (SDL_GetCurrentDisplayMode(0, &display_mode) != 0) {
        // Handle getting display mode error
        printf("SDL could not get display dimensions! SDL_Error: %s\n", SDL_GetError());
        IMG_Quit(); // Clean up SDL_image  
        SDL_Quit(); // Clean up SDL  
        return false;
    }
    SCREEN_WIDTH = 1200;
    SCREEN_HEIGHT = 720;
    MAP_WIDTH = 15;
    MAP_HEIGHT = 9;

    // Create the windows using the monitors dimensions (fullscreen) FOR RELEASE: SDL_WINDOW_FULLSCREEN
    window = SDL_CreateWindow("The Depth of Eternity", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    // Create the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);  
        IMG_Quit();  
        SDL_Quit();  
        return false;
    }
    // Load all the textures (exit if there is an error loading a texture)

    if(!loadMedia(renderer)){
        printf("Failed to load media!\n");  
        IMG_Quit();  
        SDL_Quit();  
        return false;
    }

    textures = new Textures(renderer);
    if (!textures->load()) {
        running = false;
    }

    // Disable the cursor
    tilemap = new Tilemap(renderer, textures->tilemap, 0, 0, 
    MAP_WIDTH, MAP_HEIGHT);
    tilemap->setcollisionmatrix();

    // Initialize the player object (with starting position)
    player = new Player(renderer, textures->player, 100, 100, FPS, SCREEN_WIDTH, SCREEN_HEIGHT);
    player->movement.set_Collision_Matrix(tilemap->collision_matrix);
    
    return true;
}

void Game::run() {
    // Initialize the FPS handlers
    Uint32 frame_start;
    int frame_time;
    while (running) { 
            // Get the current time
        frame_start = SDL_GetTicks();
        switch(Gamestate){
            case MENU:
                handleMenuInput();
                break;  
            case PLAYING:
                // Handle the input
                input();
        // Update the game logic
                update();
        // Render
                render();
        }
         // Control the frame rate
        frame_time = SDL_GetTicks() - frame_start;
        if (1000 / FPS > frame_time) {
            SDL_Delay(1000 / FPS - frame_time);
        }
        
    }
}

void Game::handleMenuInput(){
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
    	// If quit is detected
        if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q))) {
            // Quit the game
            running=false;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            if (isMouseInButton(&event, BUTTON_PLAY_X, BUTTON_PLAY_Y, BUTTON_PLAY_W, BUTTON_PLAY_H)) {
                running=true;
                Gamestate=PLAYING;
            }
            else if (isMouseInButton(&event, BUTTON_LOAD_X, BUTTON_LOAD_Y, BUTTON_LOAD_W, BUTTON_LOAD_H)) {
                running=true;   
                Gamestate=PLAYING; 
            } else if (isMouseInButton(&event, BUTTON_EXIT_X, BUTTON_EXIT_Y, BUTTON_EXIT_W, BUTTON_EXIT_H)) {
                running=false;
            } 
        } 
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);  
        SDL_RenderClear(renderer);  
        SDL_RenderCopy(renderer, menuBackground, NULL, NULL);  
        SDL_RenderPresent(renderer); 
        
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
    // Update tilemap
    tilemap->update();

    // Update the player
    player->update();
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    // TEST FOR HITBOXES
    // Render the tilemap object
    tilemap->render();
    // Render the player object
    player->render();

    SDL_RenderPresent(renderer);
}

bool Game::isMouseInButton(SDL_Event* event, int x, int y, int w, int h) {  
    int mouseX, mouseY;  
    SDL_GetMouseState(&mouseX, &mouseY);  
    return (mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h);  
}  

bool Game::isRunning() const {  
    return running;  
}  