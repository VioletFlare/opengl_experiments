add_executable(shaderclasstriangle
    shaderclasstriangle.cpp 
    ../glad.c 
    ../../lib/glfwevents/glfwevents.cpp
    #../../lib/glcheckerror/glcheckerror.cpp
)

target_link_libraries(shaderclasstriangle PRIVATE 
    glfw 
    ${CMAKE_DL_LIBS}
)

target_include_directories(shaderclasstriangle PRIVATE 
    .. 
    ../../lib/glfwevents
    #../../lib/glcheckerror
)

