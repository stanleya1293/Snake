#include "Renderer.h"

Renderer::Renderer() {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f
    };

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    
}

Renderer::~Renderer() {
    
};