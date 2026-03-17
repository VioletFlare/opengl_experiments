add_executable(magicsquares4vao 
    magicsquares4vao.cpp 
    ../glad.c 
    ../../lib/glfwevents/glfwevents.cpp
)

target_include_directories(magicsquares4vao PRIVATE 
    .. 
    ../../lib/glfwevents
)

target_link_libraries(magicsquares4vao PRIVATE 
    glfw 
    ${CMAKE_DL_LIBS}
)