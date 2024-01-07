#pragma once
#include <glad/glad.h>

class Texture2D {
    public:
        Texture2D();
        Texture2D(bool hasAlpha, unsigned int width, unsigned int height, unsigned char* data);
        void Generate(unsigned int width, unsigned int height, unsigned char* data);
        void Bind() const;
        unsigned int id;
        unsigned int width;
        unsigned int height;
        unsigned int internalFormat;
        unsigned int imageFormat;
        unsigned int wrap_S;
        unsigned int wrap_T;
        unsigned int filter_Min;
        unsigned int filter_Max;
};