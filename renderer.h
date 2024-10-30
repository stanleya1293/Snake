#ifndef RENDERER_H
#define RENDERER_H
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

typedef struct
{
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	unsigned int shader_program;	
} Renderer;

Renderer CreateRenderer();




#endif
