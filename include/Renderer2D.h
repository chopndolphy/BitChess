#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <memory>

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
        void initOpenGL();
        void initWindow();
        glm::vec3 clearColor = glm::vec3(0.1f, 0.1f, 0.1f);
};