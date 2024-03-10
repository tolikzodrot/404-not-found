#include "player.h"


Player::Player(SDL_Renderer* renderer, struct Texture texture, int x, int y, const float FPS, const int SW, const int SH):
renderer(renderer), texture(texture), FPS(FPS), SCREEN_WIDTH(SW), SCREEN_HEIGHT(SH) {
    rect.x = x;
    rect.y = y - HEIGHT;
    rect.w = WIDTH;
    rect.h = HEIGHT;
}

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
}

void Player::update() {
    // If there is a X moving direction
    if (direction_X) {
        // Move the player left and right
        rect.x += direction_X * speed / FPS;
    }
    if (direction_Y) {
        // Move the player up and down
        rect.y += direction_Y * speed / FPS;
    }

    // Ensure player stays within the screen boundaries
    if (rect.x < 0) {
        rect.x = 0;
    } else if (rect.x > SCREEN_WIDTH - WIDTH) {
        rect.x = SCREEN_WIDTH - WIDTH;
    }
    if (rect.y < 0) {
        rect.y = 0;
    } else if (rect.y > SCREEN_HEIGHT - HEIGHT) {
        rect.y = SCREEN_HEIGHT - HEIGHT;
    }


    

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
        looking_direction = direction_X;
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
    }
    else if (state == RUN) {
        render_texture = texture.run.texture;
        render_rect = &texture.run.frame_rects[texture.run.current_frame];
    }

    // Render the current frame
    SDL_RenderCopyEx(renderer, render_texture, render_rect, &rect, 0, nullptr, flip);

    // TEST FOR HITBOXES
    //SDL_RenderDrawRect(renderer, &rect);
    
    //SDL_RenderCopy(renderer, texture.texture, &texture.idle.frame_rects[texture.current_frame], &rect);
}
