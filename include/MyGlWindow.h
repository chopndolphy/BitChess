#pragma once
#include <GLFW/glfw3.h>

class MyGlWindow {
    public:
        MyGlWindow();
        unsigned int SCR_WIDTH = 1600;
        unsigned int SCR_HEIGHT = 1200;
        bool firstMouse = true;
        float lastX = (float)SCR_WIDTH / 2.0f;
        float lastY = (float)SCR_HEIGHT / 2.0f;
        void MoveMouse(GLFWwindow*, double xposIn, double yposIn);
        void ResizeWindow(GLFWwindow* window, int width, int height);
};