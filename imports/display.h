#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "logger.h"
class Display {
public:
    int width;
    int height;

    Display(int width,  int height, char* title);
    ~Display();
    bool isClosed();


    void update_events(SDL_Event& e);
    void update();
    void clear(float r, float g, float b, float a);

    void init_uniforms(const GLuint& program);

private:
    SDL_Window* m_window;
    bool m_isClosed;
    SDL_GLContext m_glContext;
};
