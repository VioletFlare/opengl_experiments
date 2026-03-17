#include "./../../lib/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "../../lib/glcheckerror/glcheckerror.hpp"
#include "../../lib/glfwevents/glfwevents.hpp"
#include <iostream>

struct Square {
  unsigned int VAO;
  unsigned int VBO;
  unsigned int EBO;
  unsigned int FSP;
};

int initGL(GLFWwindow *&window);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void onOffWireframe(GLFWwindow *window, int key);
void processInput(GLFWwindow *window);
Square createSquare(float *vertices, unsigned int fragmentShaderProgram);
unsigned int getVertexShaderProgram(const char *src);
unsigned int getFragmentShaderProgram(const char *src,
                                      unsigned int vertexShader);
void onOffLeftTop(GLFWwindow *window, int key);
void onOffRightTop(GLFWwindow *window, int key);
void onOffLeftBottom(GLFWwindow *window, int key);
void onOffRightBottom(GLFWwindow *window, int key);
void drawSquare(Square square);
void deleteSquare(Square square);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
bool IS_WIREFRAME = false;
bool IS_0 = true;
bool IS_1 = true;
bool IS_2 = true;
bool IS_3 = true;

const char *vertexShaderSource[1] = {
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0"};

const char *fragmentShaders[4] = {
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0",

    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
    "}\n\0",

    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\n\0",

    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
    "}\n\0",
};

int main() {
  GLFWwindow *window;
  int code = initGL(window);

  if (code < 0) {
    return code;
  }

  // build and compile our shader program
  // ------------------------------------

  unsigned int vrtxProgram = getVertexShaderProgram(vertexShaderSource[0]);
  unsigned int frgProgram0 =
      getFragmentShaderProgram(fragmentShaders[0], vrtxProgram);
  unsigned int frgProgram1 =
      getFragmentShaderProgram(fragmentShaders[1], vrtxProgram);
  unsigned int frgProgram2 =
      getFragmentShaderProgram(fragmentShaders[2], vrtxProgram);
  unsigned int frgProgram3 =
      getFragmentShaderProgram(fragmentShaders[3], vrtxProgram);

  /*

      (-0.5, 0.5)        (0.5, 0.5)
  +-----------------+
  |                 |
  |                 |
  |                 |
  +_________________+ (0.5, -0.5)
  (-0.5, -0.5)



  (-0.5, 0.5) (-0.25, 0.5)          (0.25, 0.5) (0.5, 0.5)
  (-0.5, 0.25) (-0.25, 0.5)         (0.25, 0.25) (0.5, 0.25)


  (-0.5, -0.25) (-0.25, -0.25)      (0.25, -0.25) (0.5, -0.25)
  (-0.5, -0.5) (-0.25, -0.5)        (0.25, -0.5) (0.5, -0.5)

  */

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float vertices0[] = {
      -0.5f,  0.5f,  0.0f, // (top-left sq) top-left
      -0.25f, 0.5f,  0.0f, // (top-left sq) top-right
      -0.5f,  0.25f, 0.0f, // (top-left sq) bottom-left
      -0.25f, 0.25f, 0.0f, // (top-left sq) bottom-right
  };

  float vertices1[] = {
      0.25f, 0.5f,  0.0f, // (top-right sq) top-left
      0.5f,  0.5f,  0.0f, // (top-right sq) top-right
      0.25f, 0.25f, 0.0f, // (top-right sq) bottom-left
      0.5f,  0.25f, 0.0f, // (top-right sq) bottom-right
  };

  float vertices2[] = {
      -0.5f,  -0.25f, 0.0f, // (bottom-left sq) top-left
      -0.25f, -0.25f, 0.0f, // (bottom-left sq) top-right
      -0.5f,  -0.5f,  0.0f, // (bottom-left sq) bottom-left
      -0.25f, -0.5f,  0.0f, // (bottom-left sq) bottom-right
  };

  float vertices3[] = {
      0.25f, -0.25f, 0.0f, // (bottom-right sq) top-left
      0.5f,  -0.25f, 0.0f, // (bottom-right sq) top-right
      0.25f, -0.5f,  0.0f, // (bottom-right sq) bottom-left
      0.5f,  -0.5f,  0.0f, // (bottom-right sq) bottom-right
  };

  Square sq0 = createSquare(vertices0, frgProgram0);
  Square sq1 = createSquare(vertices1, frgProgram1);
  Square sq2 = createSquare(vertices2, frgProgram2);
  Square sq3 = createSquare(vertices3, frgProgram3);

  // render loop
  // -----------
  while (!glfwWindowShouldClose(window)) {
    processInput(window);
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (IS_0) drawSquare(sq0);
    if (IS_1) drawSquare(sq1);
    if (IS_2) drawSquare(sq2);
    if (IS_3) drawSquare(sq3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------

  deleteSquare(sq0);
  deleteSquare(sq1);
  deleteSquare(sq2);
  deleteSquare(sq3);

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  return 0;
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
  window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Magic Squares 4 VAO", NULL, NULL);

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

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  glfwOnKeyup(window, GLFW_KEY_W, onOffWireframe);
  glfwOnKeyup(window, GLFW_KEY_1, onOffLeftTop);
  glfwOnKeyup(window, GLFW_KEY_2, onOffRightTop);
  glfwOnKeyup(window, GLFW_KEY_3, onOffLeftBottom);
  glfwOnKeyup(window, GLFW_KEY_4, onOffRightBottom);
}

void onOffWireframe(GLFWwindow *window, int key) {
  IS_WIREFRAME = !IS_WIREFRAME;

  if (IS_WIREFRAME) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}

void onOffLeftTop(GLFWwindow *window, int key) { IS_0 = !IS_0; }

void onOffRightTop(GLFWwindow *window, int key) { IS_1 = !IS_1; }

void onOffLeftBottom(GLFWwindow *window, int key) { IS_2 = !IS_2; }

void onOffRightBottom(GLFWwindow *window, int key) { IS_3 = !IS_3; }

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
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

void drawSquare(Square square) {
  glUseProgram(square.FSP);
  glBindVertexArray(square.VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

Square createSquare(float *vertices, unsigned int fragmentShaderProgram) {
  int indices[] = {
      0, 1, 2, // first triangle
      1, 2, 3, // second triangle
  };

  struct Square sq;

  sq.FSP = fragmentShaderProgram;

  glGenVertexArrays(1, &(sq.VAO));
  glGenBuffers(1, &(sq.VBO));
  glGenBuffers(1, &(sq.EBO));
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and
  // then configure vertex attributes(s).
  glBindVertexArray(sq.VAO);

  std::cout << sizeof(vertices) << std::endl;

  glBindBuffer(GL_ARRAY_BUFFER, sq.VBO);
  glBufferData(GL_ARRAY_BUFFER, 4 * 12, vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sq.EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * 6, indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // note that this is allowed, the call to glVertexAttribPointer registered VBO
  // as the vertex attribute's bound vertex buffer object so afterwards we can
  // safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // You can unbind the VAO afterwards so other VAO calls won't accidentally
  // modify this VAO, but this rarely happens. Modifying other VAOs requires a
  // call to glBindVertexArray anyways so we generally don't unbind VAOs (nor
  // VBOs) when it's not directly necessary.
  glBindVertexArray(0);

  return sq;
}

void deleteSquare(Square square) {
  glDeleteVertexArrays(1, &square.VAO);
  glDeleteBuffers(1, &square.VBO);
  glDeleteBuffers(1, &square.EBO);
  glDeleteProgram(square.FSP);
}