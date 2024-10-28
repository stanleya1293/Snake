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

const float quad_vertices[] = {
	-0.5f, -0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f
};

const unsigned int quad_elements[] = {
	0, 1, 2,
	0, 2, 3
}; 

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
    	GLFWwindow* window;
    	window = glfwCreateWindow(600, 600, "Snake", NULL, NULL);
    	glfwMakeContextCurrent(window);
    	gladLoadGL();
  	  	

	unsigned int v_shader;
	unsigned int f_shader;
	
	const char* v_shader_src = 
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"uniform mat4 transform;\n"
		"\n"
		"void main()\n"
		"{\n"
		"gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char* f_shader_src = 
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"\n"
		"void main()\n"
		"{\n"
		"FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
		"}\0";
	
	v_shader = glCreateShader(GL_VERTEX_SHADER);
	f_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(v_shader, 1, &v_shader_src, NULL);
	glShaderSource(f_shader, 1, &f_shader_src, NULL);
	
	int v_success;
	char v_infolog[512];
	glCompileShader(v_shader);
	glGetShaderiv(v_shader, GL_COMPILE_STATUS, &v_success);
	if (!v_success) {
		glGetShaderInfoLog(v_shader, 512, NULL, v_infolog);
		printf("Vertex Shader Error: %s", v_infolog);
	}

	int f_success;
	char f_infolog[512];
	glCompileShader(f_shader);
	glGetShaderiv(f_shader, GL_COMPILE_STATUS, &f_success);
	if (!f_success) {
		glGetShaderInfoLog(f_shader, 512, NULL, f_infolog);
		printf("Fragment Shader Error: %s", f_infolog);
	}
	
	unsigned int shader_program;
	shader_program = glCreateProgram();
	glAttachShader(shader_program, v_shader);
	glAttachShader(shader_program, f_shader);
	glLinkProgram(shader_program);
	
	glDeleteShader(v_shader);
	glDeleteShader(f_shader);

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quad_elements), quad_elements, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
	
	glUseProgram(shader_program);
	
	Direction snake_direction;
	glfwSetWindowUserPointer(window, &snake_direction);


	mat4 snake_translate;
	mat4 snake_scale;
	glm_mat4_identity(snake_scale);
	glm_scale(snake_scale, (vec3) {0.1f, 0.1f, 0.1f});
	mat4 snake_transform;
	GLint transform_location = glGetUniformLocation(shader_program, "transform");

	glfwSetKeyCallback(window, key_callback);
	Direction previous_direction;
	while (!glfwWindowShouldClose(window)) {
        	glClear(GL_COLOR_BUFFER_BIT);
		if (previous_direction != snake_direction) {
			glm_mat4_identity(snake_translate);
		}
		switch (snake_direction) {
			case SNAKE_UP:
				glm_translate(snake_translate, (vec3) {0.0f, 0.02f, 0.0f});
				break;
			case SNAKE_DOWN:
				glm_translate(snake_translate, (vec3) {0.0f, -0.02f, 0.0f});
				break;
			case SNAKE_RIGHT:
				glm_translate(snake_translate, (vec3) {0.02f, 0.0f, 0.0f});
				break;
			case SNAKE_LEFT:
				glm_translate(snake_translate, (vec3) {-0.02f, 0.0f, 0.0f});
				break;
			default:
				break;
		}
		previous_direction = snake_direction;
       		glm_mat4_mul(snake_translate, snake_scale, snake_transform);
		glUniformMatrix4fv(transform_location, 1, GL_FALSE, snake_transform[0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        	glfwSwapBuffers(window);
        	glfwPollEvents();
    	}
	glDeleteProgram(shader_program);
    	glfwTerminate();
}
