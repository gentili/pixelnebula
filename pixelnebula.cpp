#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <ctime>

#include <linmath.h>

#include "Perspective.h"
#include "Axis.h"
#include "Nebula.h"
#include "PixellationFBO.h"
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

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	cout << "Terminate due to keypress" << endl;
	glfwSetWindowShouldClose(window, 1);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	cout << "Terminate due to mouse movement" << endl;
	glfwSetWindowShouldClose(window, 1);
}

static void mouse_button_callback(GLFWwindow * window, int button, int action, int mods) {
	cout << "Terminate due to mouse press" << endl;
	glfwSetWindowShouldClose(window, 1);
}

#ifdef WIN32
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, INT nCmdShow) {
#else
int main(int argc, char ** argv) {
#endif
    srand(static_cast<unsigned> (time(0))); 
    try {
            if (!glfwInit())
                    throw runtime_error("glfwInit() failed");

			GLFWmonitor * monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode * vidmode = glfwGetVideoMode(monitor);

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
            // glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			GLFWwindow* window = glfwCreateWindow(vidmode->width, vidmode->height, "PixelNebula", monitor, NULL);
            if (!window)
                    throw runtime_error("glfwCreateWindow failed");

			glfwSetKeyCallback(window, key_callback);

			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetCursorPosCallback(window, cursor_position_callback);
            
			glfwSetMouseButtonCallback(window, mouse_button_callback);

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
                            (GLsizei) msg.length(),
                            msg.c_str());
            }

             if (!ShaderManager::Init())
                    throw runtime_error("ShaderManager::Init() failed");

            Projection projection;
            float aspect = (float) width / (float) height;
            projection.fromPerspective(1.0472f, aspect, 0.1f, 100.0f); // 60 degrees
            ShaderManager::setShaderPrograms3DProjectionMatrix(projection.asMatrix());

            float startRadius = 40;
            float curRadius = startRadius;
            float endRadius = 4;
            Camera camera;
            camera.setUpVector(0, -1, 0);
            camera.setTarget(0, 0, 0);
			camera.setRotation(0);
            camera.lookAtTarget();

            Axis axis;
            axis.setTranslation(0,0,0);

            Nebula nebula;

            PixellationFBO pixellationFBO(width,height,4);

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

                    if (curRadius > endRadius + 0.1) {
                        float totdif = startRadius - endRadius;
                        float raddif = curRadius - endRadius;

						curRadius -= raddif / totdif / 10;
                        camera.setRadius(curRadius);
                    }
                    camera.addRotation(0.001f);
                    camera.lookAtTarget();
                    pixellationFBO.begin();
                    nebula.draw();
                    pixellationFBO.end();
                    // axis.draw();

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
