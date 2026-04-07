add_executable(texturetriangle
    texturetriangle.cpp 
    ../glad.c 
    ../../lib/stb_image/stb_image.h
    ../../lib/glfwevents/glfwevents.cpp
    ../../lib/shaderloader/shader.cpp
    ../../lib/textureloader/texture.cpp
    #../../lib/glcheckerror/glcheckerror.cpp
)

target_link_libraries(texturetriangle PRIVATE 
    glfw 
    ${CMAKE_DL_LIBS}
)

target_include_directories(texturetriangle PRIVATE 
    ..
    ../../lib/stb_image
    ../../lib/glfwevents
    #../../lib/glcheckerror
    ../../lib/shaderloader
    ../../textureloader
)

