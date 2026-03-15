#include "glfwevents.hpp"
#include <GLFW/glfw3.h>

bool __glfwKeyDown = false;

void glfwOnKeyup(GLFWwindow *window, int key, GLFWEventsfun cb) {
    if (glfwGetKey(window, key) == GLFW_PRESS && __glfwKeyDown == false) {
        __glfwKeyDown = true;
    }

    if (!(glfwGetKey(window, key) == GLFW_PRESS) && __glfwKeyDown == true) {
        cb(window, key);

        __glfwKeyDown = false;
    }
}