#pragma once

#include "logger.h"

constexpr int MAX_SPRITES = 1000;


struct Vec2 {
    union {
        float values[2];
        struct {
            float x;
            float y;
        };
    };


    float& operator[](int ind) {
        return values[ind];
    }
    Vec2 operator/(float num) {
        return {x/num, y/num};
    }
    Vec2 operator-(Vec2 other) {
        return {x-other.x, y-other.y};
    }

};

struct IVec2 {
    union {
        int values[2];
        struct {
            int x;
            int y;
        };
    };
    int& operator[](int ind) {
        return values[ind];
    }
    IVec2 operator/(int num) {
        return {x/num, y/num};
    }
    IVec2 operator-(IVec2 other) {
        return {x-other.x, y-other.y};
    }

};

struct Vec4 {
    union {
        float values[4];

        struct {
            float x;
            float y;
            float z;
            float w;
        };

        struct {
            float r;
            float g;
            float b;
            float a;
        };
    };

    float& operator[](int ind) {
        return values[ind];
    }
    Vec4 operator/(float num) {
        return {x/num, y/num, z/num, w/num};
    }
    Vec4 operator-(Vec4 other) {
        return {x-other.x, y-other.y, z-other.z, w-other.w};
    }

};

struct Mat4 {
    union {
        Vec4 values[4];

        struct {
            float ax;
            float bx;
            float cx;
            float dx;

            float ay;
            float by;
            float cy;
            float dy;

            float az;
            float bz;
            float cz;
            float dz;

            float aw;
            float bw;
            float cw;
            float dw;

        };
    };
    Vec4& operator[](int ind) {
        return values[ind];
    }
};



enum SpriteID{
    SPRITE_COIN,
    SPRITE_ARROW,

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
            case SPRITE_ARROW: {
                atlas_offset = {16, 0};
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


struct OrthographicCamera2D {
    float zoom = 1.0f;
    Vec2 position;
    Vec2 dimensions;
};





Vec2 ivec2_to_vec2(IVec2 vec);
void draw_sprite(SpriteID id, Vec2 pos);
Mat4 orthographic_projection(float left, float right, float top, float bottom, float near=0.0f, float far=2.0f);
