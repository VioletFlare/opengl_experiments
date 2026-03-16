#include <GLFW/glfw3.h>

#ifndef __GLFWEVENTS__
#define __GLFWEVENTS__

#define KEYS_NUM 128

typedef void (* GLFWEventsfun)(GLFWwindow* window, int key);

void glfwOnKeyup(GLFWwindow *window, int key, GLFWEventsfun cb);

#endif