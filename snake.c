#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>


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

int main(int argc, char* argv[]) {
    	glfwInit();
    	GLFWwindow* window;
    	window = glfwCreateWindow(640, 480, "Snake", NULL, NULL);
    	glfwMakeContextCurrent(window);
    	gladLoadGL();
    	
	unsigned int v_shader;
	unsigned int f_shader;
	
	const char* v_shader_src = 
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char* f_shader_src = 
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"\n"
		"void main()\n"
		"{\n"
		"FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n"
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

	while (!glfwWindowShouldClose(window)) {
        	glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        	glfwSwapBuffers(window);
        	glfwPollEvents();
    	}
	glDeleteProgram(shader_program);
    	glfwTerminate();
}
