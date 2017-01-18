cmake_minimum_required(VERSION 3.6)
PROJECT(pixelnebula)
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

include_directories("${pixelnebula_SOURCE_DIR}/deps")
set(GLAD "${pixelnebula_SOURCE_DIR}/deps/glad/glad.h"
         "${pixelnebula_SOURCE_DIR}/deps/glad.c")

if (WIN32)
	set ( glfw3_DIR "C:\\Users\\gentili\\AppData\\Local\\CMakeBuild\\b58d18a0-84a9-8631-9016-f4ea15a8fbd2\\build\\install\\lib\\cmake\\glfw3\\" )
endif()
find_package(glfw3 REQUIRED)

ADD_EXECUTABLE(pixelnebula pixelnebula.cpp ${GLAD})
target_link_libraries(pixelnebula glfw)