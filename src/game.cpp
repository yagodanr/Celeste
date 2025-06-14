#include "imports/game.h"
RenderContext* renderContext;
GameState* gameState;


bool is_pressed[GAME_INPUT_COUNT];


EXPORT_FUNC void update_game_events(const SDL_Event &e, GameState* gameStateIn) {
    if(e.type == SDL_KEYDOWN) {
        if(e.key.keysym.sym == gameState->keyMapping[MOVE_DOWN]) {
            is_pressed[MOVE_DOWN] = true;
        }
        else if(e.key.keysym.sym == gameState->keyMapping[MOVE_UP]) {
            is_pressed[MOVE_UP] = true;
        }
        else if(e.key.keysym.sym == gameState->keyMapping[MOVE_LEFT]) {
            is_pressed[MOVE_LEFT] = true;
        }
        else if(e.key.keysym.sym == gameState->keyMapping[MOVE_RIGHT]) {
            is_pressed[MOVE_RIGHT] = true;
        }
    }
    else if(e.type == SDL_KEYUP) {
        if(e.key.keysym.sym == gameState->keyMapping[MOVE_DOWN]) {
            is_pressed[MOVE_DOWN] = false;
        }
        else if(e.key.keysym.sym == gameState->keyMapping[MOVE_UP]) {
            is_pressed[MOVE_UP] = false;
        }
        else if(e.key.keysym.sym == gameState->keyMapping[MOVE_LEFT]) {
            is_pressed[MOVE_LEFT] = false;
        }
        else if(e.key.keysym.sym == gameState->keyMapping[MOVE_RIGHT]) {
            is_pressed[MOVE_RIGHT] = false;
        }
    }
}


EXPORT_FUNC void update_game(RenderContext* renderContextIn, GameState* gameStateIn) {
    if(renderContext != renderContextIn) {
        renderContext = renderContextIn;
        gameState = gameStateIn;
    }

    if(!gameState->is_initialized) {

        renderContextIn->gameCamera.dimensions = {WORLD_WIDTH, WORLD_HEIGHT};

        gameState->is_initialized = true;
        gameState->playerPos.x = 0.0f;
        gameState->playerPos.y = 0.0f;

        gameState->keyMapping[MOVE_DOWN]    = SDLK_s;
        gameState->keyMapping[MOVE_UP]      = SDLK_w;
        gameState->keyMapping[MOVE_LEFT]    = SDLK_a;
        gameState->keyMapping[MOVE_RIGHT]   = SDLK_d;

        gameState->keyMapping[JUMP]         = SDLK_SPACE;

        for(int i=0; i<GAME_INPUT_COUNT; ++i) {
            is_pressed[i] = false;
        }
    }

    // for(float i=0; i<6; ++i) {
    //     for(float j=0; j<5; ++j) {
    //         draw_sprite(SPRITE_COIN, {i*100.0f, j*100.0f}, {100.0f, 100.0f});
    //     }
    // }1

    if(is_pressed[MOVE_DOWN]) {
        gameState->playerPos.y -= 1;
    }
    if(is_pressed[MOVE_UP]) {
        gameState->playerPos.y += 1;
    }
    if(is_pressed[MOVE_LEFT]) {
        gameState->playerPos.x -= 1;
    }
    if(is_pressed[MOVE_RIGHT]) {
        gameState->playerPos.x += 1;
    }


    draw_sprite(SPRITE_COIN, {-160.0f, -90.0f});
    draw_sprite(SPRITE_COIN, gameState->playerPos);
}

