cmake_minimum_required(VERSION 3.7)

project(Vimer.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE 1)
set(APP_VERSION_MAJOR 1)
set(APP_VERSION_MINOR 0)

set(APP_TARGET viewer.app)

# add_compile_options(-Wall -Wextra -pedantic -Werror)

add_executable(${APP_TARGET}
  main.cc)

find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

target_link_libraries(${APP_TARGET} glfw ${OPENGL_LIBRARIES})
