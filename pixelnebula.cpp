#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <linmath.h>
#include "ShaderManager.h"

using namespace std;

void abort(string msg) {
    cerr << "ABORT: " << msg << endl;
	glfwTerminate();
	exit(1);
}

int main(int argc, char ** argv) {
    //  cout << "Initialddgizing..." << endl;
    if (!glfwInit())
        abort("glfwInit() failed");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(640, 480, "PixelNebula", NULL, NULL);

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	if (!ShaderManager::Init())
		abort("ShaderManager::Init() failed");

    if (!window)
        abort("glfwCreateWindow failed");
    while (!glfwWindowShouldClose(window))
    {
		glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
