#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <cglm/cglm.h>

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
	Window window;
	window = CreateWindow(600, 600, "Snake");
	Renderer renderer;
	renderer = CreateRenderer;
	Direction snake_direction;
	glfwSetWindowUserPointer(window.WIN_ID, &snake_direction);


	mat4 snake_translate;
	mat4 snake_scale;
	glm_mat4_identity(snake_translate);
	glm_mat4_identity(snake_scale);
	glm_scale(snake_scale, (vec3) {0.1f, 0.1f, 0.1f});
	mat4 snake_transform;
	GLint transform_location = glGetUniformLocation(renderer.SHADER_PROGRAM, "transform");
	GLint color_location = glGetUniformLocation(renderer.SHADER_PROGRAM, "color");
	vec4 snake_color = {0.0f, 1.0f, 0.0f, 1.0f};

	mat4 apple_translate;
	mat4 apple_scale;
	glm_mat4_identity(apple_translate);
	glm_mat4_identity(apple_scale);
	glm_scale(apple_scale, (vec3) {0.1f, 0.1f, 0.f});
	glm_translate(apple_translate, (vec3) {0.5f, 0.3f, 0.0f});
	mat4 apple_transform;
	vec4 apple_color = {1.0f, 0.0f, 0.0f, 1.0f};
	
	glfwSetKeyCallback(window.WIN_ID, key_callback);

	double current_seconds =  glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
        	glClear(GL_COLOR_BUFFER_BIT);
		if (glfwGetTime() >= current_seconds + 0.15) {
			current_seconds = glfwGetTime();
			switch (snake_direction) {
				case SNAKE_UP:
					glm_translate(snake_translate, (vec3) {0.0f, 0.10f, 0.0f});
					break;
				case SNAKE_DOWN:
					glm_translate(snake_translate, (vec3) {0.0f, -0.10f, 0.0f});
					break;
				case SNAKE_RIGHT:
					glm_translate(snake_translate, (vec3) {0.10f, 0.0f, 0.0f});
					break;
				case SNAKE_LEFT:
					glm_translate(snake_translate, (vec3) {-0.10f, 0.0f, 0.0f});
					break;
				default:
					break;
			}
		}
       		glm_mat4_mul(snake_translate, snake_scale, snake_transform);
		glUniformMatrix4fv(transform_location, 1, GL_FALSE, snake_transform[0]);
		glUniform4fv(color_location, 1, snake_color);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glm_mat4_mul(apple_translate, apple_scale, apple_transform);
		glUniformMatrix4fv(transform_location, 1, GL_FALSE, apple_transform[0]);
		glUniform4fv(color_location, 1, apple_color);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	
        	glfwSwapBuffers(window.WIN_ID);
        	glfwPollEvents();
    	}
	glDeleteProgram(renderer.SHADER_PROGRAM);
    	glfwTerminate();
}
