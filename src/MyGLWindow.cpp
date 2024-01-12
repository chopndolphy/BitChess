#include "MyGLWindow.h"

MyGLWindow::MyGLWindow() {
    Projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), static_cast<float>(SCR_HEIGHT), 0.0f, -1.0f, 1.0f);
    BoardOffset = glm::vec2((0.2f * SCR_WIDTH), (0.1f * SCR_HEIGHT));
    BoardSize = glm::vec2((0.6f * SCR_WIDTH), 0.6f * SCR_WIDTH);
    SquareSize = glm::vec2((0.125f * BoardSize.x), (0.125f * BoardSize.y));
}
MyGLWindow::~MyGLWindow() {

}
void MyGLWindow::MoveMouse(GLFWwindow* window, double xposIn, double yposIn) {
    LastCursorPos = glm::vec2(static_cast<float>(xposIn), static_cast<float>(yposIn)); 
}
void MyGLWindow::ClickMouse(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        lastClickPos = std::make_unique<glm::vec2>(LastCursorPos);
    }
}
void MyGLWindow::ResizeWindow(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    Projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), static_cast<float>(SCR_HEIGHT), 0.0f, -1.0f, 1.0f);
    BoardOffset = glm::vec2((0.2f * SCR_WIDTH), (0.1f * SCR_HEIGHT));
    BoardSize = glm::vec2((0.6f * SCR_WIDTH), 0.6f * SCR_WIDTH);
    SquareSize = glm::vec2((0.125f * BoardSize.x), (0.125f * BoardSize.y));
}
bool MyGLWindow::GetLastClickPos(glm::vec2 &lastClick)
{
    if (!lastClickPos) {
        return false;
    } else {
        lastClick = *lastClickPos.get();
        lastClickPos.reset();
        return true;
    }
}
