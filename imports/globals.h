#pragma once

#include "rendering.h"
#include "GL/glew.h"

struct RenderContext {
    OrthographicCamera2D gameCamera;
    OrthographicCamera2D uiCamera;

    int transforms_count;
    Transform transforms[MAX_SPRITES];
};
extern RenderContext* renderContext;


struct Uniforms {
    GLuint screenSizeID;
    GLuint orthoProjID;
};
extern Uniforms* uniforms;


struct GameState {
    bool is_initialized;
};
extern GameState* gameState;
