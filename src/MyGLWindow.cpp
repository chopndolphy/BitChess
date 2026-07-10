#include "MyGLWindow.h"

void MyGLWindow::updateBoardMatrices() {
    BoardToWindow = glm::mat4(1.0f);
    BoardToWindow = glm::translate(BoardToWindow, glm::vec3(BoardOffset.x, BoardOffset.y, 0.0f));
    BoardToWindow = glm::scale(BoardToWindow, glm::vec3(SquareSize.x, SquareSize.y, 1.0f));
    WindowToBoard = glm::inverse(BoardToWindow);
}

MyGLWindow::MyGLWindow() {
    Projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), static_cast<float>(SCR_HEIGHT), 0.0f, -1.0f, 1.0f);
    BoardOffset = glm::vec2((0.2f * SCR_WIDTH), (0.1f * SCR_HEIGHT));
    BoardSize = glm::vec2((0.6f * SCR_WIDTH), 0.6f * SCR_WIDTH);
    SquareSize = glm::vec2((0.125f * BoardSize.x), (0.125f * BoardSize.y));
    updateBoardMatrices();
}
MyGLWindow::~MyGLWindow() {

}
void MyGLWindow::MoveMouse(GLFWwindow* window, double xposIn, double yposIn) {
    float scaleX = 1.0f, scaleY = 1.0f;
    glfwGetWindowContentScale(window, &scaleX, &scaleY);
    LastCursorPos = glm::vec2(static_cast<float>(xposIn) * scaleX, static_cast<float>(yposIn) * scaleY);
}
void MyGLWindow::ClickMouse(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos = 0.0, ypos = 0.0;
        glfwGetCursorPos(window, &xpos, &ypos);
        float scaleX = 1.0f, scaleY = 1.0f;
        glfwGetWindowContentScale(window, &scaleX, &scaleY);
        lastClickPos = std::make_unique<glm::vec2>(static_cast<float>(xpos) * scaleX, static_cast<float>(ypos) * scaleY);
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
    updateBoardMatrices();
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
