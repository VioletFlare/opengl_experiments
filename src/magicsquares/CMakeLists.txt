add_executable(magicsquares
    magicsquares.cpp 
    ../glad.c 
    ../../lib/glfwevents/glfwevents.cpp
)

target_include_directories(magicsquares PRIVATE 
    .. 
    ../../lib/glfwevents
)

target_link_libraries(magicsquares PRIVATE 
    glfw 
    ${CMAKE_DL_LIBS}
)