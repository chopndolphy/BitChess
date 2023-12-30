#include "ResourceManager.h"
#include "Shader.h"
#include "Texture2D.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <stb_image.h>

std::unordered_map<std::string, std::shared_ptr<Texture2D>> ResourceManager::Textures;
std::unordered_map<std::string, std::shared_ptr<Shader>> ResourceManager::Shaders;

std::weak_ptr<Shader> ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name) {
    Shaders.try_emplace(name, std::make_shared<Shader>(std::move(loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile))));
    return Shaders[name];
}
std::weak_ptr<Shader> ResourceManager::GetShader(std::string name) {
    return Shaders[name];
}
std::weak_ptr<Texture2D> ResourceManager::LoadTexture(const char* file, bool alpha, std::string name) {
    Textures.try_emplace(name, std::make_shared<Texture2D>(std::move(loadTextureFromFile(file, alpha))));
    return Textures[name];
}
std::weak_ptr<Texture2D> ResourceManager::GetTexture(std::string name) {
    return Textures[name];
}
void ResourceManager::Clear() {
    for (auto iter : Shaders) {
        glDeleteProgram(iter.second->ID);
    }
    for (auto iter : Textures) {
        glDeleteTextures(1, &iter.second->id);
    }
}
Shader ResourceManager::loadShaderFromFile(const char* vertexPath, const char* fragmentPath, const char* geometryPath) {
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::ifstream gShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    gShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream, gShaderStream;
        // read file's ubffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        //convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        if (geometryPath != nullptr) {
            gShaderFile.open(geometryPath);
            gShaderStream << gShaderFile.rdbuf();
            gShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    } catch (std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        std::cout << vertexPath << std::endl;
        throw std::runtime_error("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ");
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();
    Shader shader;
    shader.compile(vShaderCode, fShaderCode, geometryPath != nullptr ? gShaderCode : nullptr);
    return shader;
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