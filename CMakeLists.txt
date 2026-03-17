cmake_minimum_required(VERSION 3.10)
project(OpenGLExperiments)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)

add_subdirectory(src/magicsquares4vao)