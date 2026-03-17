add_executable(magic_squares 
    magicsquares4vao.cpp 
    ../glad.c 
    ../../lib/glfwevents/glfwevents.cpp
)

target_include_directories(magic_squares PRIVATE 
    .. 
    ../../lib/glfwevents
)

target_link_libraries(magic_squares PRIVATE 
    glfw 
    ${CMAKE_DL_LIBS}
)