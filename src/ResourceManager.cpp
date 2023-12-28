#include "ResourceManager.h"
#include "Shader.h"
#include "Texture2D.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <stb_image.h>

std::map<std::string, Texture2D> ResourceManager::Textures;
std::map<std::string, Shader> ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name) {
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}
Shader ResourceManager::GetShader(std::string name) {
    return Shaders[name];
}
Texture2D ResourceManager::LoadTexture(const char* file, bool alpha, std::string name) {
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}
Texture2D ResourceManager::GetTexture(std::string name) {
    return Textures[name];
}
void ResourceManager::Clear() {
    for (auto iter : Shaders) {
        glDeleteProgram(iter.second.ID);
    }
    for (auto iter : Textures) {
        glDeleteTextures(1, &iter.second.id);
    }
}
Shader ResourceManager::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile) {
    // NEED TO MOVE SHADER LOADING HERE (CURRENTLY IN SPRITE)
}
Texture2D ResourceManager::loadTextureFromFile(const char* file, bool alpha) {
    Texture2D texture;
    if (alpha) {
        texture.internalFormat = GL_RGBA;
        texture.imageFormat = GL_RGBA;
    }
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    texture.Generate(width, height, data);
    stbi_image_free(data);
    return texture;
}