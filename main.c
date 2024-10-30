#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cglm/cglm.h>
#include "renderer.h"
#include "snake.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
       	Snake* snake = glfwGetWindowUserPointer(window);
	if (action == GLFW_PRESS) {
		switch(key) {
			case GLFW_KEY_W:
				snake->direction = SNAKE_UP;
				break;
			case GLFW_KEY_S:
				snake->direction = SNAKE_DOWN;
				break;
			case GLFW_KEY_A:
				snake->direction = SNAKE_LEFT;
				break;
			case GLFW_KEY_D:
				snake->direction = SNAKE_RIGHT;
				break;
			default: 
				break;	
		}	
	}
}

int main(int argc, char* argv[]) {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(600, 600, "Snake", NULL, NULL);
	glfwMakeContextCurrent(window);
	Renderer renderer;
	renderer = CreateRenderer();
	Snake* snake = Create_Snake();
	glfwSetWindowUserPointer(window, snake);
	
	int apple_x, apple_y;
	apple_x = 12;
	apple_y = 14;
	mat4 apple_translate;
	mat4 apple_scale;
	glm_mat4_identity(apple_translate);
	glm_mat4_identity(apple_scale);
	glm_scale(apple_scale, (vec3) {0.05f, 0.05f, 0.05f});
	glm_translate(apple_translate, (vec3) {0.15f, 0.35f, 0.0f});
	mat4 apple_transform;
	vec4 apple_color = {1.0f, 0.0f, 0.0f, 1.0f};
	
	GLint transform_location = glGetUniformLocation(renderer.shader_program, "transform");
	GLint color_location = glGetUniformLocation(renderer.shader_program, "color");

	glfwSetKeyCallback(window, key_callback);
	int apple_prev_x;
	int apple_prev_y;
	double current_seconds =  glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
        	glClear(GL_COLOR_BUFFER_BIT);
		if (glfwGetTime() >= current_seconds + 0.15) {
			current_seconds = glfwGetTime();
			switch (snake->direction) {
				case SNAKE_UP:
					snake->y = snake->y + 1;
					break;
				case SNAKE_DOWN:
					snake->y = snake->y - 1; 
					break;
				case SNAKE_RIGHT:
					snake->x = snake->x + 1;
					break;
				case SNAKE_LEFT:
					snake->x = snake->x - 1;
					break;
				default:
					break;
			}
		}
		if (snake->x == 21 || snake->x == 0 || snake->y == 21 || snake->y == 0) {
			glfwSetWindowShouldClose(window, 1);
		}
		if (snake->x == apple_x && snake->y == apple_y) {
			apple_prev_x = apple_x;
			apple_prev_y = apple_y;
			srand(time(NULL));
			apple_x = (rand() % 20) + 1;
			printf("apple_x: %d \n", apple_x);
			srand(time(NULL) + 20);
			apple_y = (rand() % 20) + 1;
			printf("apple_y: %d \n", apple_y);
			glm_translate(apple_translate, (vec3) 
					{(float) ((apple_x - apple_prev_x) * 30) / 300, 
					(float) ((apple_y - apple_prev_y) * 30) / 300, 0.0f});
			
		}
       		Draw_Snake(snake, renderer);

		glm_mat4_mul(apple_translate, apple_scale, apple_transform);
		glUniformMatrix4fv(transform_location, 1, GL_FALSE, apple_transform[0]);
		glUniform4fv(color_location, 1, apple_color);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        	glfwSwapBuffers(window);
        	glfwPollEvents();
    	}
	glDeleteProgram(renderer.shader_program);
    	glfwTerminate();
}
