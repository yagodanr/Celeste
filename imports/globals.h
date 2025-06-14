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



// #############################################################################
//                          Game globals
// #############################################################################

enum GameInputType {
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_UP,
    MOVE_DOWN,
    JUMP,


    GAME_INPUT_COUNT
};

struct GameState {
    bool is_initialized;
    Vec2 playerPos;
    int keyMapping[GAME_INPUT_COUNT];
};
extern GameState* gameState;
