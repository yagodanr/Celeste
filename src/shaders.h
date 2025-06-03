#pragma once

#include <GL/glew.h>

#include "memo.h"

#define VERTEX_SHADER_SOURCE "assets/shaders/quad.vert"
#define FRAG_SHADER_SOURCE "assets/shaders/quad.frag"



class Shaders {
public:
    Shaders(BumpAllocator* bumpAllocator);
    virtual ~Shaders();


private:

    void init_shaders(BumpAllocator* bumpAllocator);
    static GLuint create_shader(const char* source, const int sourceSize, GLenum shaderType, BumpAllocator* bumpAllocator);

    // have to rewrite code, add next initializations of shaders if this enum is changed
    enum {
        VERTEX_SHADER,
        FRAGMENT_SHADER,

        NUM_SHADERS
    };

    GLuint m_shaders[NUM_SHADERS];
    GLuint m_program;
};

