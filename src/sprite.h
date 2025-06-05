#pragma once

#include "logger.h"

constexpr int MAX_SPRITES = 1000;


struct Vec2 {
    float x;
    float y;
};

struct IVec2 {
    int x;
    int y;
};


enum SpriteID{
    SPRITE_COIN,

    SPITES_COUT
};

struct Sprite {
public:
    IVec2 atlas_offset;
    IVec2 spriteSize;

    Sprite(SpriteID id) {
        switch(id) {
            case SPRITE_COIN: {
                atlas_offset = {0, 0};
                spriteSize = {16, 16};
                break;
            }
            default: {
                SM_ASSERT(false, "Wrong SpriteID");
                break;
            }
        }
    }
};


struct Transform {
    IVec2 atlas_offset;
    IVec2 spriteSize;
    Vec2 pos;
    Vec2 size;

};

struct RenderContext {
    int transforms_count;
    Transform transforms[MAX_SPRITES];
};
extern RenderContext renderContext;


void draw_sprite(SpriteID id, Vec2 pos, Vec2 size);