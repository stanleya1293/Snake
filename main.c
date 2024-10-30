#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cglm/cglm.h>
#include "renderer.h"



typedef enum {
	SNAKE_UP,
	SNAKE_DOWN,
	SNAKE_RIGHT,
	SNAKE_LEFT	
} Direction; 

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Direction* snake_direction;
       	snake_direction = glfwGetWindowUserPointer(window);
	if (action == GLFW_PRESS) {
		switch(key) {
			case GLFW_KEY_W:
				*snake_direction = SNAKE_UP;
				break;
			case GLFW_KEY_S:
				*snake_direction = SNAKE_DOWN;
				break;
			case GLFW_KEY_A:
				*snake_direction = SNAKE_LEFT;
				break;
			case GLFW_KEY_D:
				*snake_direction = SNAKE_RIGHT;
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
	Direction snake_direction;
	glfwSetWindowUserPointer(window, &snake_direction);

	int snake_x, snake_y;
	snake_x = 10;
	snake_y = 10;
	mat4 snake_translate;
	mat4 snake_scale;
	glm_mat4_identity(snake_translate);
	glm_mat4_identity(snake_scale);
	glm_translate(snake_translate, (vec3) {-0.05, -0.05f, 0.0f});
	glm_scale(snake_scale, (vec3) {0.05f, 0.05f, 0.05f});
	mat4 snake_transform;
	GLint transform_location = glGetUniformLocation(renderer.shader_program, "transform");
	GLint color_location = glGetUniformLocation(renderer.shader_program, "color");
	vec4 snake_color = {0.0f, 1.0f, 0.0f, 1.0f};
	
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

	glfwSetKeyCallback(window, key_callback);
	int apple_prev_x;
	int apple_prev_y;
	double current_seconds =  glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
        	glClear(GL_COLOR_BUFFER_BIT);
		if (glfwGetTime() >= current_seconds + 0.15) {
			current_seconds = glfwGetTime();
			switch (snake_direction) {
				case SNAKE_UP:
					glm_translate(snake_translate, (vec3) {0.0f, 0.10f, 0.0f});
					snake_y = snake_y + 1;
					break;
				case SNAKE_DOWN:
					glm_translate(snake_translate, (vec3) {0.0f, -0.10f, 0.0f});
					snake_y = snake_y - 1; 
					break;
				case SNAKE_RIGHT:
					glm_translate(snake_translate, (vec3) {0.10f, 0.0f, 0.0f});
					snake_x = snake_x + 1;
					break;
				case SNAKE_LEFT:
					glm_translate(snake_translate, (vec3) {-0.10f, 0.0f, 0.0f});
					snake_x = snake_x - 1;
					break;
				default:
					break;
			}
		}
		if (snake_x == 21 || snake_x == 0 || snake_y == 21 || snake_y == 0) {
			glfwSetWindowShouldClose(window, 1);
		}
		if (snake_x == apple_x && snake_y == apple_y) {
			apple_prev_x = apple_x;
			apple_prev_y = apple_y;
			srand(time(NULL));
			apple_x = (rand() % 20) + 1;
			printf("apple_x: %d \n", apple_x);
			srand(time(NULL) + 20);
			apple_y = (rand() % 20) + 1;
			printf("apple_y: %d \n", apple_y);
			glm_translate(apple_translate, (vec3) {(float) ((apple_x - apple_prev_x) * 30) / 300, (float) ((apple_y - apple_prev_y) * 30) / 300, 0.0f});
			
		}
       		glm_mat4_mul(snake_translate, snake_scale, snake_transform);
		glUniformMatrix4fv(transform_location, 1, GL_FALSE, snake_transform[0]);
		glUniform4fv(color_location, 1, snake_color);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


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
