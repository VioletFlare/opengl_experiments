add_executable(texturesquare
    texturesquare.cpp 
    ../glad.c 
    ../../lib/stb_image/stb_image.h
    ../../lib/glfwevents/glfwevents.cpp
    ../../lib/shaderloader/shader.cpp
    ../../lib/textureloader/texture.cpp
    #../../lib/glcheckerror/glcheckerror.cpp
)

target_link_libraries(texturesquare PRIVATE 
    glfw 
    ${CMAKE_DL_LIBS}
)

target_include_directories(texturesquare PRIVATE 
    ..
    ../../lib/stb_image
    ../../lib/glfwevents
    #../../lib/glcheckerror
    ../../lib/shaderloader
    ../../textureloader
)

