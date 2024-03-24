#include "player.h"


Player::Player(SDL_Renderer* renderer, struct Texture texture, const int x, const int y, const float FPS, const int SW, const int SH)
: movement(x,y,0,SW,SH), renderer(renderer), FPS(FPS), SCREEN_WIDTH(SW), SCREEN_HEIGHT(SH),texture(texture) {
    rect.x = x;
    rect.y = y;
    rect.w = WIDTH;
    rect.h = HEIGHT;
}
//initialize the state of the player
Player::~Player() {
}

void Player::handle_input(SDL_Event event) {
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
            case SDLK_a:
                direction_X = -1;
                break;
            case SDLK_d:
                direction_X = 1;
                break;
            case SDLK_w:
                direction_Y = -1;
                break;
            case SDLK_s:
                direction_Y = 1;
                break;
        }
    }
    //according to the keystokens changing the moving direction
    else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_a:
                if (direction_X == -1) {
                    direction_X = 0;
                }
                break;
            case SDLK_d:
                if (direction_X == 1) {
                    direction_X = 0;
                }
                break;
            case SDLK_w:
                if (direction_Y == -1) {
                    direction_Y = 0;
                }
                break;
            case SDLK_s:
                if (direction_Y == 1) {
                    direction_Y = 0;
                }
                break;
        }
    }
    //key release,stop moving
}

void Player::update() {
    
    movement.setSpeed(speed / FPS);
    movement.setDirection(direction_X, direction_Y);
    movement.move(&rect);

    // Set the player states
    if (direction_X) {
        state = RUN;
    }else if(direction_Y){
        state = RUN;
    }
    else {
        // Set the state to idle
        state = IDLE;
    }

    // Set the looking direction
    if (direction_X) {
        looking_direction = direction_X;//set the face direction,right or left
    }

    // If enough time has passed between frames
    if ((SDL_GetTicks() - texture.frame_start) > (FPS / texture.render_speed)) {
        // Update the specific state animations current frame
        if (state == IDLE) {
            texture.idle.current_frame = (texture.idle.current_frame + 1) % texture.idle.num_of_frames;
        }
        else if (state == RUN) {
            texture.run.current_frame = (texture.run.current_frame + 1) % texture.run.num_of_frames;
        }
        
        // Get the frame start again
        texture.frame_start = SDL_GetTicks();
    }
}

void Player::render() {
    // Flip the texture depending on the looking direction
    SDL_RendererFlip flip = (looking_direction == 1) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

    // Set the rendering texture according to the players state
    SDL_Texture* render_texture;
    SDL_Rect* render_rect;
    if (state == IDLE) {
        render_texture = texture.idle.texture;
        render_rect = &texture.idle.frame_rects[texture.idle.current_frame];
    }else
    // if (state == RUN) 
    {
        render_texture = texture.run.texture;
        render_rect = &texture.run.frame_rects[texture.run.current_frame];
    }

    // Render the current frame
    SDL_RenderCopyEx(renderer, render_texture, render_rect, &rect, 0, nullptr, flip);
    collision_visual();
    // TEST FOR HITBOXES
    //SDL_RenderDrawRect(renderer, &rect);
    
    //SDL_RenderCopy(renderer, texture.texture, &texture.idle.frame_rects[texture.current_frame], &rect);
}
void Player::collision_visual(){
    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    //SDL_RenderDrawRect(renderer, movement.getRect());
    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
