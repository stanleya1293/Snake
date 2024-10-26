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

void draw_square() {
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(vbo);
} 

int main(int argc, char* argv[]) {
    	glfwInit();
    	GLFWwindow* window;
    	window = glfwCreateWindow(640, 480, "Snake", NULL, NULL);
    	glfwMakeContextCurrent(window);
    	gladLoadGL();
    	while (!glfwWindowShouldClose(window)) {
        	glClear(GL_COLOR_BUFFER_BIT);
        	glfwSwapBuffers(window);
        	glfwPollEvents();
    	}
    	glfwTerminate();
}
