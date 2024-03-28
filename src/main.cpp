#include <SDL2/SDL.h>  
#include <stdbool.h>  
#include <stdio.h>  
#include<SDL2/SDL_image.h>

#include "game.h" 

#define BUTTON_PLAY_X 608  
#define BUTTON_PLAY_Y 344 
#define BUTTON_PLAY_W 344
#define BUTTON_PLAY_H 84 
#define BUTTON_LOAD_X 556
#define BUTTON_LOAD_Y 552
#define BUTTON_LOAD_W 96 
#define BUTTON_LOAD_H 184
#define BUTTON_EXIT_X 764
#define BUTTON_EXIT_Y 452
#define BUTTON_EXIT_W 184
#define BUTTON_EXIT_H 96
  
SDL_Texture* menuBackground;  
SDL_Texture* playButton;  
SDL_Texture* loadButton;  
SDL_Texture* exitButton;   

bool initSDL() {  
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {  
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());  
        return false;  
    }  
  
    return true;  
}  
  
bool loadMedia(SDL_Renderer* renderer) {  
    const char* menuBackgroundPath= "assets/tiles/menu/menuBackgroundPath.png";
    const char* playButtonPath="assets/tiles/menu/playButtonPath.png";
    const char* loadbuttonPath="assets/tiles/menu/loadbuttonPath.png";
    const char* exitButtonPath="assets/tiles/menu/exitButtonPath.png";
    menuBackground = IMG_LoadTexture(renderer, menuBackgroundPath);  
    playButton = IMG_LoadTexture(renderer, playButtonPath);  
    loadButton = IMG_LoadTexture(renderer, loadbuttonPath);  
    exitButton = IMG_LoadTexture(renderer, exitButtonPath);  
    if (menuBackground == NULL || playButton == NULL || loadButton == NULL || exitButton == NULL) {  
        printf("Failed to load media!\n");  
        return false;  
    }  
  
    return true;  
}  
  
bool isMouseInButton(SDL_Event* event, int x, int y, int w, int h) {  
    int mouseX, mouseY;  
    SDL_GetMouseState(&mouseX, &mouseY);  
    return (mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h);  
}  
  
void closeSDL() {  
    SDL_DestroyTexture(menuBackground);  
    SDL_DestroyTexture(playButton);  
    SDL_DestroyTexture(loadButton);  
    SDL_DestroyTexture(exitButton);  
    IMG_Quit();  
    SDL_Quit();  
}  
  
int main() {  
    Game game;
    SDL_Window* window;  
    SDL_Renderer* renderer;  
    SDL_Event event;  
    bool quit = false;  
    int image=1;
    if (!initSDL()) {  
        printf("Failed to initialize SDL!\n");  
    } else {  
        window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 960, 576, SDL_WINDOW_SHOWN);  
        if (window == NULL) {  
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());  
        } else {  
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);  
            if (renderer == NULL) {  
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());  
            } else {  
                if (!loadMedia(renderer)) {  
                    printf("Failed to load media!\n");  
                } else {  

                    while (!quit) {  
                    
                        while (SDL_PollEvent(&event) != 0) {  
                             
                            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q))) {  
                                quit = true;  
                            }
                            
                            else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                                    if (isMouseInButton(&event, BUTTON_PLAY_X, BUTTON_PLAY_Y, BUTTON_PLAY_W, BUTTON_PLAY_H)) {
                                       image=2;
                                        if (!game.init()) {
                                            printf("Failed to initialize the game!\n");
                                            return 1;
                                        }
                                        game.run();
                                        return 0;
                                        printf("PLAY button clicked!\n");
                                       
                                    } else if (isMouseInButton(&event, BUTTON_LOAD_X, BUTTON_LOAD_Y, BUTTON_LOAD_W, BUTTON_LOAD_H)) {
                                        image=3;
                                        printf("LOAD button clicked!\n");
                                        
                                        } else if (isMouseInButton(&event, BUTTON_EXIT_X, BUTTON_EXIT_Y, BUTTON_EXIT_W, BUTTON_EXIT_H)) {
                                        image=4;
                                        quit = true;
                                        printf("EXIT button clicked!\n");
                                            
                                            }
                                        }
                                    
                        }
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);  
                    SDL_RenderClear(renderer);  
 
                    
                    if(image==1) SDL_RenderCopy(renderer, menuBackground, NULL, NULL);  
                    if(image==2) SDL_RenderCopy(renderer, playButton, NULL, NULL);  
                    if(image==3) SDL_RenderCopy(renderer, loadButton, NULL, NULL);  
                    if(image==4) SDL_RenderCopy(renderer, exitButton, NULL, NULL);  
                   
                    /*SDL_Rect playButtonRect = {BUTTON_PLAY_X, BUTTON_PLAY_Y, BUTTON_PLAY_W, BUTTON_PLAY_H};  
                    SDL_RenderCopy(renderer, playButton, NULL, &playButtonRect);  
  
                    SDL_Rect loadButtonRect = {BUTTON_LOAD_X, BUTTON_LOAD_Y, BUTTON_LOAD_W, BUTTON_LOAD_H};  
                    SDL_RenderCopy(renderer, loadButton, NULL, &loadButtonRect);  
  
                    SDL_Rect exitButtonRect = {BUTTON_EXIT_X, BUTTON_EXIT_Y, BUTTON_EXIT_W, BUTTON_EXIT_H};  
                    SDL_RenderCopy(renderer, exitButton, NULL, &exitButtonRect);
                   */

                    SDL_RenderPresent(renderer);  
                }  
            }  
        }  
    }  
}  
 
// 释放资源并退出  
closeSDL();  
return 0;

}
