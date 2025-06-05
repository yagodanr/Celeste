#include "game.h"



void update_game() {
    for(float i=0; i<20; ++i) {
        for(float j=0; j<11; ++j) {
            draw_sprite(SPRITE_COIN, {i*100.0f, j*100.0f}, {100.0f, 100.0f});
        }
    }
}

