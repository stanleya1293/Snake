#ifndef RENDERER_H
#define RENDERER_H
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

typedef struct {
	float* QUAD_VERTICES;
	unsigned int* QUAD_INDICES;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	unsigned int SHADER_PROGRAM;	
} Renderer;

typedef struct {
	GLFWwindow* WIN_ID;
	int WIN_WIDTH;
	int WIN_HEIGHT;
	char* WIN_TITLE;
} Window;


Window CreateWindow(int width, int height, char* title);

Renderer CreateRenderer();




#endif
