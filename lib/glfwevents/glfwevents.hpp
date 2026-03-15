#include <GLFW/glfw3.h>

#ifndef __GLFWEVENTS__
#define __GLFWEVENTS__

typedef void (* GLFWEventsfun)(GLFWwindow* window, int key);

void glfwOnKeyup(GLFWwindow *window, int key, GLFWEventsfun cb);

#endif