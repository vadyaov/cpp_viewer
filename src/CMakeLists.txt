cmake_minimum_required(VERSION 3.7)
project(Vimer.1)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_VERBOSE_MAKEFILE 1)
set(APP_VERSION_MAJOR 1)
set(APP_VERSION_MINOR 0)

set(APP_TARGET vimer.app)

# add_compile_options(-Wall -Wextra -pedantic -Werror -Wno-unused-variable)
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

add_subdirectory(imgui)
include_directories(${PROJECT_SOURCE_DIR})
add_executable(${APP_TARGET}
  imgui_glfw_window.cc
  imgui/imgui-knobs.cpp
  main.cc)
target_link_libraries(${APP_TARGET} imgui ${CMAKE_SOURCE_DIR}/matrix_lib/build/s21_matrix_oop.a)

# glfw
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# glew
find_package(GLEW 2.0 REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

# SDL
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

if (APPLE)
    # find_library(COCOA_LIBRARY Cocoa)
    find_library(OpenGL_LIBRARY OpenGL)
    # find_library(IOKIT_LIBRARY IOKit)
    # find_library(COREVIDEO_LIBRARY CoreVideo)
    SET(EXTRA_LIBS ${OpenGL_LIBRARY})
endif (APPLE)

target_link_libraries(
        ${APP_TARGET}
        glfw
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${EXTRA_LIBS}
        ${SDL2_LIBRARIES}
)
