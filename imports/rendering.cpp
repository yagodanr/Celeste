#include "rendering.h"

RenderContext* renderContext;


void draw_sprite(SpriteID id, Vec2 pos, Vec2 size) {
    Sprite s(id);

    Transform t = {};
    t.atlas_offset = s.atlas_offset;
    t.spriteSize = s.spriteSize;
    t.pos = pos;
    t.size = size;

    renderContext->transforms[renderContext->transforms_count++] = t;
}
