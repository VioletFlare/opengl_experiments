#ifndef TEXTURE_H
#define TEXTURE_H

#include "../glad/include/glad/glad.h"
#include "../stb_image/stb_image.h"

class Texture {
  public:
    unsigned int ID;
    Texture();
    Texture(const char *path, int width, int height, int nrChannels);
    void use();
};

#endif