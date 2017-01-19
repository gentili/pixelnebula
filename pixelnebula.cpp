#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <linmath.h>
#include "ShaderManager.h"

using namespace std;

void abort(string msg) {
}

int main(int argc, char ** argv) {
    //  cout << "Initialddgizing..." << endl;
	try {
		if (!glfwInit())
			throw runtime_error("glfwInit() failed");
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		GLFWwindow* window = glfwCreateWindow(640, 480, "PixelNebula", NULL, NULL);

		glfwMakeContextCurrent(window);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		glfwSwapInterval(1);

		if (!ShaderManager::Init())
			throw runtime_error("ShaderManager::Init() failed");

		if (!window)
			throw runtime_error("glfwCreateWindow failed");
		while (!glfwWindowShouldClose(window))
		{
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glfwTerminate();
		return 0;
	}
	catch (const exception & e) {
		cerr << "ABORT: " << e.what() << endl;
		glfwTerminate();
		throw e;
	}
}
