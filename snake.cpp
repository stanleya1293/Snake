#include <glad/glad.h>
#include <GLFW/glfw3.h>


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
