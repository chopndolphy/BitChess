#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

class MyGLWindow {
    public:
        MyGLWindow();
        ~MyGLWindow();
        unsigned int SCR_WIDTH = 1600;
        unsigned int SCR_HEIGHT = 1200;
        void MoveMouse(GLFWwindow* window, double xposIn, double yposIn);
        void ClickMouse(GLFWwindow* window, int button, int action, int mods);
        void ResizeWindow(GLFWwindow* window, int width, int height);
        bool GetLastClickPos(glm::vec2 &lastClick);
        glm::mat4 Projection;
        glm::vec2 LastCursorPos;
        glm::vec2 BoardOffset;
        glm::vec2 BoardSize;
        glm::vec2 SquareSize;
        /** Maps board space (0,0)-(8,8) to window pixel space. */
        glm::mat4 BoardToWindow;
        /** Maps window pixel space to board space. Inverse of BoardToWindow. */
        glm::mat4 WindowToBoard;
    private:
        void updateBoardMatrices();
        std::unique_ptr<glm::vec2> lastClickPos;
        bool firstMouse = true;
        float lastX = (float)SCR_WIDTH / 2.0f;
        float lastY = (float)SCR_HEIGHT / 2.0f;
};