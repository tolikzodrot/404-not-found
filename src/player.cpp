#include "player.h"


Player::Player(SDL_Renderer* renderer, struct Texture texture, const int x, const int y, const float FPS, const int SW, const int SH)
: movement(0,SW,SH), renderer(renderer), FPS(FPS),texture(texture) {
    rect.x = x;
    rect.y = y;
    rect.w = WIDTH;
    rect.h = HEIGHT;
    sword_rect.x = x;
    sword_rect.y = y;
    sword_rect.w = SWORD_WIDTH;
    sword_rect.h = SWORD_HEIGHT;
    start_time_degree = SDL_GetTicks();
    start_time_swing = SDL_GetTicks();
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
            swordRotation = initialSwordRotation;
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

    

    movement.move(&rect, 1, kickback.x, kickback.y);
    kickback.x *= 0.9;
    kickback.y *= 0.9;

    movement.setSpeed(speed / FPS);
    movement.setDirection(direction_X, direction_Y);
    movement.move(&rect);

    center = {sword_rect.w / 2, sword_rect.h / 2};

    if (direction_X) {
        looking_direction = direction_X; // set the face direction, right or left
    }

    if (attack == ATTACK) {
        sword_rect.x = rect.x;
        sword_rect.y = rect.y;
    }else{

    }
    

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
    if(attack == ATTACK && attackState == HALT && SDL_GetTicks() - start_time_swing > 500){
        start_time_swing = SDL_GetTicks();
        attackState = SWING;
    }
    float angle_change_per_second = 400.0f; // Change this to the desired value
    if(attackState == SWING){
        swordRotation += angle_change_per_second * ((SDL_GetTicks() - start_time_degree) / 1000.0f);
    }
    start_time_degree = SDL_GetTicks();
    float max_sword_angle = 390.0f; // Change this to the desired value
    if (swordRotation >= max_sword_angle) {
        // If it has, reset the sword rotation to its initial value
        swordRotation = initialSwordRotation;
        attackState = HALT;
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
    SDL_Texture* sword_render_texture;
    SDL_Rect* render_rect;
    if (state == IDLE) {
        render_texture = texture.idle.texture;
        render_rect = &texture.idle.frame_rects[texture.idle.current_frame];
    }else if (state == RUN) {
        render_texture = texture.run.texture;
        render_rect = &texture.run.frame_rects[texture.run.current_frame];
    }else{
        render_texture = texture.idle.texture;
        render_rect = &texture.idle.frame_rects[texture.idle.current_frame];
    }

    if (state == ATTACK && attackState == SWING) {
        sword_render_texture = texture.sword1.texture;
        double sword_rotation_render = swordRotation;
        if (flip == 1){
            sword_rotation_render = 180 - swordRotation;
        }
        sword_rect_rotated = calculateRectWithAngle(sword_rect, (sword_rotation_render * M_PI) / 180, 80);
        SDL_RenderCopyEx(renderer, sword_render_texture, NULL, &sword_rect_rotated, flip ? -swordRotation-30 : swordRotation+30, &center, flip);
    }

    // Render the current frame
    SDL_RenderCopyEx(renderer, render_texture, render_rect, &rect, 0, nullptr, flip);

    render_texture = texture.heart.texture;
    SDL_Rect heart_rect = {0, 0, 40, 40};
    for (int i = 0; i < HP; i++) {
        heart_rect.x = i * 40;
        SDL_RenderCopy(renderer, render_texture, NULL, &heart_rect);
    }

    // TEST FOR HITBOXES
    //SDL_RenderDrawRect(renderer, &rect);
    //SDL_RenderCopy(renderer, texture.texture, &texture.idle.frame_rects[texture.current_frame], &rect);
}

SDL_Rect Player::calculateRectWithAngle(const SDL_Rect &originalRect, double angle, double radius) {
    // Calculate the new center coordinates
    int centerX = originalRect.x + originalRect.w / 2;
    int centerY = originalRect.y + originalRect.h / 2;

    // Calculate the new center coordinates after applying the angle and radius
    int newX = static_cast<int>(centerX + radius * std::cos(angle));
    int newY = static_cast<int>(centerY + radius * std::sin(angle));

    // Create a new SDL_Rect with the same dimensions as the original
    SDL_Rect newRect;
    newRect.x = newX - originalRect.w / 2; // Adjusting for the top-left corner
    newRect.y = newY - originalRect.h / 2;
    newRect.w = originalRect.w;
    newRect.h = originalRect.h;

    return newRect;
}

void Player::isHit(SDL_Rect enemy){

    if(SDL_HasIntersection(&rect, &enemy) && SDL_GetTicks() - invinsibility > 500){
        invinsibility = SDL_GetTicks();
        HP--;
        kickback.x = rect.x - enemy.x;
        kickback.y = rect.y - enemy.y;

        // Normalize the kickback direction
        float length = sqrt(kickback.x * kickback.x + kickback.y * kickback.y);
        kickback.x /= length;
        kickback.y /= length;
        // Multiply by the desired kickback magnitude
        kickback.x *= 10;
        kickback.y *= 10;
        
    }
    if(HP == 0)
        state = DEAD;
}

SDL_Rect Player::getSwordRect(){
    if(state == ATTACK && attackState == SWING){
        return sword_rect_rotated;
    }else{
        SDL_Rect empty = {0,0,0,0};
        return empty;
    }
}

SDL_Rect Player::getRect(){
    return rect;
}