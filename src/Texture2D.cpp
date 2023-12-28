#include "Texture2D.h"

Texture2D::Texture2D() {
    width = 0;
    height = 0;
    internalFormat = GL_RGB;
    imageFormat = GL_RGB;
    wrap_S = GL_REPEAT;
    wrap_T = GL_REPEAT;
    filter_Min = GL_LINEAR;
    filter_Max = GL_LINEAR;

    glGenTextures(1, &this->id); 
}
void Texture2D::Generate(unsigned int width, unsigned int height, unsigned char* data) {
    this->width = width;
    this->height = height;

    glBindTexture(GL_TEXTURE_2D, this->id);
    glTexImage2D(GL_TEXTURE_2D, 0, this->internalFormat, width, height, 0, this->imageFormat, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_Max);

    glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture2D::Bind() const {
    glBindTexture(GL_TEXTURE_2D, this->id);
}