#include <glad/glad.h>
#include <GLFW/glfw3.h>


const float quad_vertices[] = {
	-0.5f, -0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f
};

const int quad_elements[] = {
	0, 1, 2,
	0, 3, 4
}; 

int main(int argc, char* argv[]) {
    	glfwInit();
    	GLFWwindow* window;
    	window = glfwCreateWindow(640, 480, "Snake", NULL, NULL);
    	glfwMakeContextCurrent(window);
    	gladLoadGL();
    	
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), &vbo, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), &ebo, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);

	while (!glfwWindowShouldClose(window)) {
        	glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        	glfwSwapBuffers(window);
        	glfwPollEvents();
    	}
    	glfwTerminate();
}
