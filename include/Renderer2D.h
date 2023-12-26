#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

void mouse_callback(GLFWwindow*, double xposIn, double yposIn);

class Renderer2D {
    public:
        Renderer2D();
        ~Renderer2D();
        void PrepareFrame();
        void ProcessInput();
        void RenderFrame();
        void EndFrame();
        bool IsRunning();
        const static unsigned int SCR_WIDTH = 1600;
        const static unsigned int SCR_HEIGHT = 1200;
        float deltaTime = 0.0f;
        float lastFrame = 0.0f;
    private:
        GLFWwindow* window;
        void initOpenGL();
        void initWindow();
        glm::vec3 clearColor = glm::vec3(0.1f, 0.1f, 0.1f);
        GLFWframebuffersizefun framebuffer_size_callback(GLFWwindow* window, int width, int height);

};

bool firstMouse = true;
float lastX = (float)Renderer2D::SCR_WIDTH / 2.0f;
float lastY = (float)Renderer2D::SCR_HEIGHT / 2.0f;

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;
}