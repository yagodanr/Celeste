#include "globals.h"

#include "rendering.h"

Vec2 ivec2_to_vec2(IVec2 vec) {
    Vec2 res = {};
    res.x = (float)vec.x;
    res.y = (float)vec.y;

    return res;
}


void draw_sprite(SpriteID id, Vec2 pos) {
    Sprite s(id);

    Transform t = {};
    t.atlas_offset = s.atlas_offset;
    t.spriteSize = s.spriteSize;
    t.size = ivec2_to_vec2(s.spriteSize);
    t.pos = pos - t.size/2.0f;

    if(renderContext->transforms_count >= MAX_SPRITES) {
        SM_ASSERT(false, "Too many transforms to render. Over the limit of MAX_SPRITES");
        return;
    }

    renderContext->transforms[renderContext->transforms_count++] = t;
}

// TODO Why this hell works like that and does not care about many things
Mat4 orthographic_projection(float left, float right, float top, float bottom, float near, float far) {
    Mat4 proj = {};

    proj[0][0] = 2.0f / (right-left);
    proj[1][1] = -2.0f / (top-bottom);
    proj[2][2] = 2.0f / (far-near);
    proj[3][3] = 1.0f;

    // 3-d column, i-th row
    proj[3][0] = -(right+left)/(right-left);
    proj[3][1] = (top+bottom)/(top-bottom);
    proj[3][2] = (far+near)/(far-near);

    return proj;
}

