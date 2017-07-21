cmake_minimum_required(VERSION 3.6)
PROJECT(pixelnebula)
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
set(DEPS "${pixelnebula_SOURCE_DIR}/deps/glad/glad.h"
         "${pixelnebula_SOURCE_DIR}/deps/glad.c"
         "${pixelnebula_SOURCE_DIR}/deps/linmath.h")

find_package(glfw3 REQUIRED)

if (WIN32)
	set(MAKE_WIN_EXE "WIN32")
endif()

ADD_EXECUTABLE(pixelnebula 
	${MAKE_WIN_EXE}
	pixelnebula.cpp 
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
