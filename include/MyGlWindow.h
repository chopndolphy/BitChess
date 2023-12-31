#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class MyGlWindow {
    public:
        MyGlWindow();
        ~MyGlWindow();
        unsigned int SCR_WIDTH = 1600;
        unsigned int SCR_HEIGHT = 1200;
        bool firstMouse = true;
        float lastX = (float)SCR_WIDTH / 2.0f;
        float lastY = (float)SCR_HEIGHT / 2.0f;
        void MoveMouse(GLFWwindow* window, double xposIn, double yposIn);
        void ResizeWindow(GLFWwindow* window, int width, int height); 
        glm::vec2 lastCursorPos;
};