#include <GLFW/glfw3.h>

#ifndef __GLCHECKERROR__
#define __GLCHECKERROR__

GLenum glCheckError_(const char *file, int line);

#define glCheckError() glCheckError_(__FILE__, __LINE__);

#endif