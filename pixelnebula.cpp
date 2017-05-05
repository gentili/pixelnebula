#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <linmath.h>
#include "ShaderManager.h"
#include "Perspective.h"
#include "Axis.h"
#include "utils.h"

using namespace std;

void APIENTRY debugCallBack(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar *msg,
	const void *data) {
	cout << "GL_DEBUG: " << msg << endl;
}

int main(int argc, char ** argv) {
    //  cout << "Initializing..." << endl;

	try {
		if (!glfwInit())
			throw runtime_error("glfwInit() failed");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		GLFWwindow* window = glfwCreateWindow(640, 480, "PixelNebula", NULL, NULL);
		if (!window)
			throw runtime_error("glfwCreateWindow failed");

		glfwMakeContextCurrent(window);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		glfwSwapInterval(1);

                int width, height;
                glfwGetFramebufferSize(window,&width,&height);

                cout << "Window size " << width << "x" << height << endl;

		GLint v;
		glGetIntegerv(GL_CONTEXT_FLAGS, &v);
		if (v & GL_CONTEXT_FLAG_DEBUG_BIT) {
			cout << "Debug Callback Enabled" << endl;
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(debugCallBack, nullptr);
			GLuint noIds = 0;
			glDebugMessageControl(GL_DONT_CARE,
				GL_DONT_CARE,
				GL_DONT_CARE,
				0,
				&noIds,
				true);
			string msg = "GL Debug Facility seems to be working";
			glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION,
				GL_DEBUG_TYPE_OTHER,
				0,
				GL_DEBUG_SEVERITY_NOTIFICATION,
				msg.length(),
				msg.c_str());
		}

		if (!ShaderManager::Init())
			throw runtime_error("ShaderManager::Init() failed");

		Projection projection;
		float aspect = (float) width / (float) height;
		projection.fromPerspective(1.0472f, aspect, 0.1f, 10.0f); // 60 degrees
		ShaderManager::setShaderPrograms3DProjectionMatrix(projection.asMatrix());

		Camera camera;
		// camera.setRadius(4.5f);
		camera.setUpVector(0, 1, 0);
		camera.setTarget(0, 0, 0);
		camera.setPosition(0, 0, -4.5f);
		camera.lookAtTarget();

                Axis axis;
                axis.setTranslation(0,0,0);

		GLuint vaoId;
		glGenVertexArrays(1, &vaoId);
		glBindVertexArray(vaoId);
		while (!glfwWindowShouldClose(window))
		{
			checkGLError();

			ShaderManager::setShaderPrograms3DViewMatrix(camera.asMatrix());

                        glViewport(0,0,width,height);
                        glScissor(0,0,width,height);
                        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                        axis.draw();

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
