#include "shaders.h"
#include "sprite.h"

Shaders::Shaders(BumpAllocator* bumpAllocator) {

    this->init_shaders(bumpAllocator);


    this->m_program = glCreateProgram();
    for(int i=0; i<NUM_SHADERS; ++i) {
        glAttachShader(this->m_program, this->m_shaders[i]);
    }
    glLinkProgram(this->m_program);

    // We can delete, because they're already attached
    for(int i=0; i<NUM_SHADERS; ++i) {
        glDetachShader(this->m_program, this->m_shaders[i]);
        glDeleteShader(this->m_shaders[i]);
    }

    // In this project Vertex array is not needed, but without it OpenGL wouldn't work. Probably...
    GLuint VAO;
    glCreateVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_GREATER);

    this->screenSizeID = glGetUniformLocation(this->m_program, "screenSize");

    // Transform Storage buffer
    {
        GLuint SBO;
        glGenBuffers(1, &SBO);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, SBO);
        glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Transform)*MAX_SPRITES, renderContext.transforms, GL_DYNAMIC_DRAW);
    }

}
Shaders::~Shaders() {
    glDeleteProgram(this->m_program);

}

void Shaders::bind() {
    glUseProgram(this->m_program);
}



void Shaders::init_shaders(BumpAllocator* bumpAllocator) {

    long vertexSize = 0;
    char* vertexSource = read_file(VERTEX_SHADER_SOURCE, &vertexSize, bumpAllocator);
    long fragSize = 0;
    char* fragSource = read_file(FRAG_SHADER_SOURCE, &fragSize, bumpAllocator);

    this->m_shaders[VERTEX_SHADER] = create_shader(vertexSource, (int)vertexSize, GL_VERTEX_SHADER, bumpAllocator);
    this->m_shaders[FRAGMENT_SHADER] = create_shader(fragSource, (int)fragSize, GL_FRAGMENT_SHADER, bumpAllocator);
}

GLuint Shaders::create_shader(const char* source, const int sourceSize, GLenum shaderType, BumpAllocator* bumpAllocator) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, 0);
    glCompileShader(shader);

    // Check if compiled successfully;
    {
        int success = 0;
        char compilationLog[2048] = {};

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(shader, 2048, 0, compilationLog);
            SM_ASSERT(false, "Shader compilation failed: %s", compilationLog);
        }
    }


    return shader;
}
