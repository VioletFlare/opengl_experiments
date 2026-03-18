add_executable(magicsquaresparametrized
    magicsquaresparametrized.cpp 
    ../glad.c 
    ../../lib/glfwevents/glfwevents.cpp
    #../../lib/glcheckerror/glcheckerror.cpp
)

target_link_libraries(magicsquaresparametrized PRIVATE 
    glfw 
    ${CMAKE_DL_LIBS}
)

target_include_directories(magicsquaresparametrized PRIVATE 
    .. 
    ../../lib/glfwevents
    #../../lib/glcheckerror
)

