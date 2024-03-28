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


// This function is responsible for handling player input.
// It takes an SDL_Event as a parameter and updates the player's state accordingly.
void Player::handle_input(SDL_Event event) {

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            attack = ATTACK; // Set the attack state when the left mouse button is pressed
        }
    }

    else if (event.type == SDL_MOUSEBUTTONUP) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            attack = IDLE; // Set the idle state when the left mouse button is released
        }
    }

    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
            case SDLK_a:
                direction_X = -1; // Set the X direction to -1 when the 'a' key is pressed
                break;
            case SDLK_d:
                direction_X = 1; // Set the X direction to 1 when the 'd' key is pressed
                break;
            case SDLK_w:
                direction_Y = -1; // Set the Y direction to -1 when the 'w' key is pressed
                break;
            case SDLK_s:
                direction_Y = 1; // Set the Y direction to 1 when the 's' key is pressed
                break;
        }
    }
    //according to the keystokens changing the moving direction
    else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_a:
                if (direction_X == -1) {
                    direction_X = 0; // Set the X direction to 0 when the 'a' key is released
                }
                break;
            case SDLK_d:
                if (direction_X == 1) {
                    direction_X = 0; // Set the X direction to 0 when the 'd' key is released
                }
                break;
            case SDLK_w:
                if (direction_Y == -1) {
                    direction_Y = 0; // Set the Y direction to 0 when the 'w' key is released
                }
                break;
            case SDLK_s:
                if (direction_Y == 1) {
                    direction_Y = 0; // Set the Y direction to 0 when the 's' key is released
                }
                break;
        }
    }
    //key release,stop moving
}


// This function is responsible for updating the player's state.
void Player::update() {
    
    movement.setSpeed(speed / FPS);
    movement.setDirection(direction_X, direction_Y);
    movement.move(&rect);

    // Set the player states
    if (attack == ATTACK) {
        state = ATTACK;
    }else if (direction_X) {
        state = RUN;
    }else if(direction_Y){
        state = RUN;
    }else {
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
        }else if (state == ATTACK) {
            texture.attack.current_frame = (texture.attack.current_frame + 1) % texture.attack.num_of_frames;
        }
        
        // Get the frame start again
        texture.frame_start = SDL_GetTicks();
    }
}
// This function is responsible for rendering the player on the screen.
// It flips the texture depending on the looking direction and sets the rendering texture according to the player's state.
// Then it renders the current frame using SDL_RenderCopyEx function.
// After rendering, it calls the collision_visual function to visualize the collision rectangle.
// Uncomment the SDL_RenderDrawRect function to test hitboxes.
void Player::render() {
    // Flip the texture depending on the looking direction
    SDL_RendererFlip flip = (looking_direction == 1) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

    // Set the rendering texture according to the players state
    SDL_Texture* render_texture;
    SDL_Rect* render_rect;
    if (state == IDLE) {
        render_texture = texture.idle.texture;
        render_rect = &texture.idle.frame_rects[texture.idle.current_frame];
    }else if (state == RUN) {
        render_texture = texture.run.texture;
        render_rect = &texture.run.frame_rects[texture.run.current_frame];
    }else{
        render_texture = texture.attack.texture;
        render_rect = &texture.attack.frame_rects[texture.attack.current_frame];
    }

    // Render the current frame
    SDL_RenderCopyEx(renderer, render_texture, render_rect, &rect, 0, nullptr, flip);
    collision_visual();
}
void Player::collision_visual(){

}
