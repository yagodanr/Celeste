#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture::Texture() {
    int width, height, channels;
    char* filename = TEXTURE_PATH;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 4);
    if(!data) {
        SM_ASSERT(false, "Failed loading texture");
    }

    glGenTextures(1, &this->m_texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE0, this->m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8_ALPHA8, width, height,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, data);


    stbi_image_free(data);

    // Don't rely on textures colorspace. Otherwise every texture would be darker
    glEnable(GL_FRAMEBUFFER_SRGB);
    glDisable(0x809D); // disable multisampling


}
