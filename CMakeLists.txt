cmake_minimum_required(VERSION 3.6)
PROJECT(pixelnebula)
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
set(DEPS "${pixelnebula_SOURCE_DIR}/deps/glad/glad.h"
         "${pixelnebula_SOURCE_DIR}/deps/glad.c"
         "${pixelnebula_SOURCE_DIR}/deps/linmath.h")

if (WIN32)
	set ( glfw3_DIR "C:\\Users\\gentili\\AppData\\Local\\CMakeBuild\\b58d18a0-84a9-8631-9016-f4ea15a8fbd2\\build\\install\\lib\\cmake\\glfw3\\" )
endif()
find_package(glfw3 REQUIRED)

ADD_EXECUTABLE(pixelnebula pixelnebula.cpp 
    utils.h utils.cpp 
    ShaderManager.h ShaderManager.cpp 
    Shaders.h 
    Perspective.h Perspective.cpp 
    Renderable.h Renderable.cpp 
    Axis.h Axis.cpp 
    PointStar.h PointStar.cpp
    DoublePointStar.h
    GlowSphere.h GlowSphere.cpp
    Nebula.h Nebula.cpp
    PixellationFBO.h PixellationFBO.cpp
    ${DEPS})
set_property(TARGET pixelnebula PROPERTY CXX_STANDARD 11)
target_link_libraries(pixelnebula glfw)
target_include_directories(pixelnebula PUBLIC "${pixelnebula_SOURCE_DIR}/deps")
