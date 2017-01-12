#include <string>
#include <iostream>

#include <GLFW/glfw3.h>

using namespace std;

void abort(string msg) {
    cerr << "ABORT: " << msg;
    exit(1);
}

int main(int argc, char ** argv) {
    cout << "Initializing..." << endl;
    if (!glfwInit())
        abort("glfwInit failed");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (!window)
        abort("glfwCreateWindow failed");
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
