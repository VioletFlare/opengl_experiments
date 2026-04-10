#include "./../../lib/glad/include/glad/glad.h"
#include "./../../lib/shaderloader/shader.hpp"
#include "./../../lib/textureloader/texture.hpp"
#include <GLFW/glfw3.h>

#include <iostream>

struct Square {
  unsigned int VBO;
  unsigned int EBO;
  Shader shader;
  Texture texture;
};

struct DrawingContext {
    unsigned int VAO;
} ctx;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
int initGL(GLFWwindow *&window);
unsigned int getVertexShaderProgram(const char *src);
unsigned int getFragmentShaderProgram(const char *src,
                                      unsigned int vertexShader);
Square createSquare(float *vertices, unsigned int szvert, unsigned int *indices, unsigned int szindices, Shader shader, Texture texture);
void drawSquare(Square square);
void deletesquare(Square square);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    GLFWwindow *window;
    int code = initGL(window);

    if (code < 0) {
        return code;
    }

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // bottom-left  
        0.0f, 0.5f, 0.0f, 1.0f, //color
        -0.5f, -0.5f, //tex

        -0.5f, 0.5f, 0.0f,  // top-left
        0.0f, 0.5f, 0.0f, 1.0f,
        -0.5f, 0.5f,

        0.5f,  0.5f, 0.0f,  // top-right   
        0.0f, 0.5f, 0.0f, 1.0f, //color
        0.5f,  0.5f, //tex

        0.5f, -0.5f, 0.0f, // bottom-right 
        0.0f, 0.5f, 0.0f, 1.0f, //color
        0.5f, -0.5f //tex
    }; 

    unsigned int indices[] = {
        0, 1, 2, // first triangle
        0, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &ctx.VAO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(ctx.VAO);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Shader shader("shaders/texturesquare/shader.vs\0", "shaders/texturesquare/shader.fs\0");
    Texture texture("assets/texturesquare/container.jpg\0", 100, 100, 1);
    
    shader.use();

    glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0);

    Square sq0 = createSquare(vertices, sizeof(vertices), indices, sizeof(indices), shader, texture);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        drawSquare(sq0);
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &ctx.VAO);
    deletesquare(sq0);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

int initGL(GLFWwindow *&window) {
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // glfw window creation
  // --------------------
  window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Shader Class square", NULL, NULL);

  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  return 0;
}

unsigned int getVertexShaderProgram(const char *src) {
  // vertex shader
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &src, NULL);
  glCompileShader(vertexShader);
  // check for shader compile errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  return vertexShader;
}

unsigned int getFragmentShaderProgram(const char *src,
                                      unsigned int vertexShader) {
  int success;
  char infoLog[512];

  // fragment shader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &src, NULL);
  glCompileShader(fragmentShader);
  // check for shader compile errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  // link shaders
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // check for linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return shaderProgram;
}

Square createSquare(float *vertices, unsigned int szvert, unsigned int *indices, unsigned int szindices, Shader shader, Texture texture) {
    Square sq;

    sq.shader = shader;
    sq.texture = texture;

    glGenBuffers(1, &sq.VBO);
    glGenBuffers(1, &sq.EBO);

    glBindBuffer(GL_ARRAY_BUFFER, sq.VBO);
    glBufferData(GL_ARRAY_BUFFER, szvert, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sq.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, szindices, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) (3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2); 

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 

    return sq;
}

void drawSquare(Square square) {
    // draw our first square
    square.shader.use();
    square.texture.use();
    glBindVertexArray(ctx.VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void deletesquare(Square square) {
    glDeleteBuffers(1, &(square.VBO));
    glDeleteBuffers(1, &(square.EBO));
}