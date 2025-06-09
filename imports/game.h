#pragma once
#include "globals.h"
#include "platform_specific.h"

#include "rendering.h"


constexpr int WORLD_WIDTH = 320;
constexpr int WORLD_HEIGHT = 180;
constexpr int TILE_SIZE = 8;


extern "C" {
    EXPORT_FUNC void update_game(RenderContext* renderContextIn, GameState* gameStateIn);

}