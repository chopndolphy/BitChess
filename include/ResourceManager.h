#pragma once

#include <glad/glad.h>

#include <map>
#include <string>

class Shader;
class Texture2D;

class ResourceManager {
    public:
        static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
        static Shader GetShader(std::string name);
        static Texture2D LoadTexture(const char* file, bool alpha, std::string name);
        static Texture2D GetTexture(std::string name);
        static void Clear();
        static std::map<std::string, Shader> Shaders;
        static std::map<std::string, Texture2D> Textures;
    private:
        ResourceManager() {}
        static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
        static Texture2D loadTextureFromFile(const char* file, bool alpha);
};