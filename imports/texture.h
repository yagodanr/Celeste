#pragma once

#include <GL/glew.h>


#include "logger.h"
#include "rendering.h"


#define TEXTURE_PATH "assets/textures/texture_atlas.png"

class Texture {
public:
    Texture();


private:
    GLuint m_texture;
    GLuint m_SBO;
};

