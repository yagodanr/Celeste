#include "imports/game.h"
RenderContext* renderContext;
GameState* gameState;


EXPORT_FUNC void update_game(RenderContext* renderContextIn, GameState* gameStateIn) {
    if(renderContext != renderContextIn) {
        renderContext = renderContextIn;
        gameState = gameStateIn;
    }

    if(!gameState->is_initialized) {

        renderContextIn->gameCamera.dimensions = {WORLD_WIDTH, WORLD_HEIGHT};

        gameState->is_initialized = true;
    }

    // for(float i=0; i<6; ++i) {
    //     for(float j=0; j<5; ++j) {
    //         draw_sprite(SPRITE_COIN, {i*100.0f, j*100.0f}, {100.0f, 100.0f});
    //     }
    // }

    renderContext->gameCamera.position.x = 0;
    renderContext->gameCamera.position.y = 0;
    draw_sprite(SPRITE_COIN, {0.0f, 50.0f});
}

