cmake_minimum_required(VERSION 3.10)
project(OpenGLExperiments)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/build" CACHE PATH "Installation Prefix" FORCE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin/")

find_package(glfw3 REQUIRED)

add_subdirectory(src/magicsquares)
add_subdirectory(src/magicsquares4vao)