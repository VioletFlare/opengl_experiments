#include "glfwevents.hpp"
#include <GLFW/glfw3.h>

int __keysDown[KEYS_NUM] = { -1 };

bool isKeyDown(int key) {
    for (int i = 0; i < KEYS_NUM; i++) {
        if (__keysDown[i] == key) {
            return true;
        }
    }

    return false;
}

void setKeyDown(int key) {
    for (int i = 0; i < KEYS_NUM; i++) {
        if (__keysDown[i] == -1) {
            __keysDown[i] = key;
            return;
        }
    }
}

void setKeyUp(int key) {
    for (int i = 0; i < KEYS_NUM; i++) {
        if (__keysDown[i] == key) {
            __keysDown[i] = -1;
            return;
        }
    }
}

void glfwOnKeyup(GLFWwindow *window, int key, GLFWEventsfun cb) {
    if (glfwGetKey(window, key) == GLFW_PRESS && !isKeyDown(key)) {
        setKeyDown(key);
    }

    if (!(glfwGetKey(window, key) == GLFW_PRESS) && isKeyDown(key)) {
        cb(window, key);

        setKeyUp(key);
    }
}