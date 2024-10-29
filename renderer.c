#include "renderer.h"

Window CreateWindow(int width, int height, char* title) {
	glfwInit();
	Window window;
	window.WIN_WIDTH = width;
	window.WIN_HEIGHT = height;
	window.WIN_TITLE = title;
    	window.WIN_ID = glfwCreateWindow(window.WIN_WIDTH, window.WIN_HEIGHT, window.WIN_TITLE, NULL, NULL);
	glfwMakeContextCurrent(window.WIN_ID);
	return window;
}

Renderer CreateRenderer() {	
	Renderer renderer;
	gladLoadGL();
	
	renderer.QUAD_VERTICES = {
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
	 	 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f
	};

	renderer.QUAD_INDICES = {
		0, 1, 2,
		0, 2, 3
	}; 
	unsigned int f_shader;
	unsigned int v_shader;

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
		"uniform vec4 color;\n"
		"\n"
		"void main()\n"
		"{\n"
		"FragColor = color;\n"
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
	
	renderer.SHADER_PROGRAM = glCreateProgram();
	glAttachShader(renderer.SHADER_PROGRAM, v_shader);
	glAttachShader(renderer.SHADER_PROGRAM, f_shader);
	glLinkProgram(renderer.SHADER_PROGRAM);
	
	glDeleteShader(v_shader);
	glDeleteShader(f_shader);

	glGenVertexArrays(1, &renderer.VAO);
	glBindVertexArray(renderer.VAO);

	glGenBuffers(1, &renderer.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, renderer.VBO);

	glGenBuffers(1, &renderer.EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer.EBO);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(renderer.QUAD_VERTICES), renderer.QUAD_VERTICES, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(renderer.QUAD_INDICES), renderer.QUAD_INDICES, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
	
	glUseProgram(shader_program);
};
