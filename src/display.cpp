#include "display.h"


#ifdef DEBUG
static void APIENTRY gl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                         GLsizei length, const GLchar* message, const void* user)
{
  if(severity == GL_DEBUG_SEVERITY_LOW ||
     severity == GL_DEBUG_SEVERITY_MEDIUM ||
     severity == GL_DEBUG_SEVERITY_HIGH)
  {
    SM_ASSERT(false, "OpenGL Error: %s", message);
  }
  else
  {
    SM_TRACE((char*)message);
  }
}

#endif





Display::Display(int width, int height, char* title) {
    SDL_Init(SDL_INIT_EVERYTHING);


    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);  // Depth buffer bits for 3D
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);  // Stencil buffer bits
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1); // Hardware acceleration
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    this->width = width;
    this->height = height;

    this->m_window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );
    if(!this->m_window) {
        SM_ASSERT(false, "Failed to create window");
        return;
    }

    this->m_glContext = SDL_GL_CreateContext(this->m_window);
    if(!this->m_glContext) {
        SM_ASSERT(false, "Failed to create GLContext");
        return;
    }

    GLenum status = glewInit();
    if(status != GLEW_OK) {
        SM_ASSERT(false, "Failed to initialize GL");
        return;
    }
    this->m_isClosed = false;
    // might break down on multiwindows or multithreading
    SDL_GL_MakeCurrent(this->m_window, this->m_glContext); // make context current (Claude suggested)


    #ifdef DEBUG
    glDebugMessageCallback(&gl_debug_callback, nullptr);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glEnable(GL_DEBUG_OUTPUT);
    #endif
}

Display::~Display() {
    SDL_GL_DeleteContext(this->m_glContext);
    SDL_DestroyWindow(this->m_window);
    SDL_Quit();
}

bool Display::isClosed() {
    return this->m_isClosed;
}

void Display::update() {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        switch(e.type) {
            case SDL_QUIT:
                this->m_isClosed = true;
                break;
            case SDL_WINDOWEVENT:
                if(e.window.event == SDL_WINDOWEVENT_RESIZED || e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    SDL_GetWindowSize(this->m_window, &this->width, &this->height);
                    glViewport(0, 0, this->width, this->height); // update size for OpenGL(Claude)
                }
        }

    }

    SDL_GL_SwapWindow(this->m_window);

}

void Display::clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClearDepth(0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


