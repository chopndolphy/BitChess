#pragma once

#include <glad/glad.h>

#include <unordered_map>
#include <string>
#include <memory>

class Shader;
class Texture2D;

class ResourceManager {
    public:
        static std::weak_ptr<Shader> LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
        static std::weak_ptr<Shader> GetShader(std::string name);
        static std::weak_ptr<Texture2D> LoadTexture(const char* file, bool alpha, std::string name);
        static std::weak_ptr<Texture2D> GetTexture(std::string name);
        static void Clear();
        static std::unordered_map<std::string, std::shared_ptr<Shader>> Shaders;
        static std::unordered_map<std::string, std::shared_ptr<Texture2D>> Textures;
    private:
        ResourceManager() {}
        static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
        static Texture2D loadTextureFromFile(const char* file, bool alpha);
};