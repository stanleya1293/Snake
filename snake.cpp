#include "includes.h"

int main(int argc, char* argv[]) {
    glfwInit();
    GLFWwindow* window;
    window = glfwCreateWindow(640, 480, "Snake", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGL();
    Renderer renderer;
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}