#include "imports/game.h"


EXPORT_FUNC void update_game(RenderContext* renderContextIn) {
    if(renderContext != renderContextIn) {
        renderContext = renderContextIn;
    }
    for(float i=0; i<6; ++i) {
        for(float j=0; j<5; ++j) {
            draw_sprite(SPRITE_COIN, {i*100.0f, j*100.0f}, {100.0f, 100.0f});
        }
    }
}

