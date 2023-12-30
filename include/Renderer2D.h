#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include "Sprite.h"
#include "MyGlWindow.h"
#include "Texture2D.h"
class Renderer2D {
    public:
        Renderer2D();
        ~Renderer2D();
        void PrepareFrame();
        void ProcessInput();
        void RenderFrame();
        void EndFrame();
        bool IsRunning();
        void UpdateBoardState(std::string boardState);
        float deltaTime = 0.0f;
        float lastFrame = 0.0f;
    private:
        GLFWwindow* window;
        std::shared_ptr<MyGlWindow> myWindow;
        std::unordered_map<std::string, std::unique_ptr<Sprite>> uiElements;
        std::vector<std::unique_ptr<Sprite>> pieces;
        std::weak_ptr<Texture2D> textureMap;
        void initOpenGL();
        void initWindow();
        void initShadersAndTextures();
        void initUIElements();
        glm::vec2 indexToPosition(size_t boardIndex);
        glm::vec3 clearColor = glm::vec3(0.1f, 0.1f, 0.1f);
        glm::mat4 projection;
        glm::vec2 boardOffset;
        glm::vec2 boardSize;
        glm::vec2 pieceSize;
};