#pragma once

#include <GL/glew.h>


#include "logger.h"



#define TEXTURE_PATH "assets/textures/texture_atlas.png"

class Texture {
public:
    Texture();


private:
    GLuint m_texture;
};

