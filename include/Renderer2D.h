#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <memory>

class Sprite;
class MyGlWindow;
class Renderer2D {
    public:
        Renderer2D();
        ~Renderer2D();
        void PrepareFrame();
        void ProcessInput();
        void RenderFrame();
        void EndFrame();
        bool IsRunning();
        float deltaTime = 0.0f;
        float lastFrame = 0.0f;
    private:
        GLFWwindow* window;
        MyGlWindow* myWindow;
        Sprite* spriteRenderer;
        void initOpenGL();
        void initWindow();
        void initSprites();
        glm::vec3 clearColor = glm::vec3(0.1f, 0.1f, 0.1f);
        glm::mat4 projection;
};