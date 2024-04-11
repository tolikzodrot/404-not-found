#include "enemy.h"

Enemy::Enemy(SDL_Renderer* renderer, struct Texture texture, const int x, const int y, const float FPS, const int SW, const int SH)
: movement(0,SW,SH), renderer(renderer), FPS(FPS),texture(texture) {
    rect.x = x;
    rect.y = y;
    rect.w = WIDTH;
    rect.h = HEIGHT;
    state = IDLE;
}

Enemy::~Enemy() {
}

void Enemy::update() {
    if(state == DEAD){
        return;
    }

    int enemy_center_x = rect.x + rect.w / 2;
    int enemy_center_y = rect.y + rect.h / 2;
    int target_center_x = target.x + target.w / 2;
    int target_center_y = target.y + target.h / 2;

    int dx = target_center_x - enemy_center_x;
    int dy = target_center_y - enemy_center_y;

    float length = sqrt(dx * dx + dy * dy);
    float direction_x = dx / length;
    float direction_y = dy / length;

    int move_x = direction_x * speed / FPS;
    int move_y = direction_y * speed / FPS;

    if(SDL_HasIntersection(&rect, &target)){
        halt = SDL_GetTicks();
    }
    if(SDL_GetTicks() - halt > 500){
        movement.move(&rect, 1, move_x, move_y);
    }

    if(move_x > 0){
        looking_direction = 1;
    }else{
        looking_direction = -1;
    }

    if ((SDL_GetTicks() - texture.frame_start) > (FPS / texture.render_speed)) {
        if (state == IDLE) {
            texture.idle.current_frame = (texture.idle.current_frame + 1) % texture.idle.num_of_frames;
        }
        else if (state == RUN) {
            texture.run.current_frame = (texture.run.current_frame + 1) % texture.run.num_of_frames;
        }else if (state == ATTACK) {
            texture.attack.current_frame = (texture.attack.current_frame + 1) % texture.attack.num_of_frames;
        }
        texture.frame_start = SDL_GetTicks();
    }
}

void Enemy::render() {
    if(state == DEAD){
        return;
    }

    SDL_RendererFlip flip = (looking_direction == 1) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;


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

    SDL_RenderCopyEx(renderer, render_texture, render_rect, &rect, 0, nullptr, flip);
}

void Enemy::isHit(SDL_Rect sword){
    if(SDL_HasIntersection(&rect, &sword)){
        state = DEAD;
    }
}

int Enemy::check_state(){
    if(state == DEAD){
        return 0;
    }else{
        return 1;
    }
}

void Enemy::targetUpdate(SDL_Rect rect){
    target = rect;
}

void Enemy::setState(){
    state = IDLE;
}

void Enemy::setPos(int x, int y){
    rect.x = x;
    rect.y = y;
}