#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

class MyGlWindow {
    public:
        MyGlWindow();
        ~MyGlWindow();
        unsigned int SCR_WIDTH = 1600;
        unsigned int SCR_HEIGHT = 1200;
        void MoveMouse(GLFWwindow* window, double xposIn, double yposIn);
        void ClickMouse(GLFWwindow* window, int button, int action, int mods);
        bool GetLastClickPos(glm::vec2 &lastClick);
        glm::vec2 LastCursorPos;
    private:
        std::unique_ptr<glm::vec2> lastClickPos;
        bool firstMouse = true;
        float lastX = (float)SCR_WIDTH / 2.0f;
        float lastY = (float)SCR_HEIGHT / 2.0f;
};