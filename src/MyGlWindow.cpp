#include "MyGlWindow.h"

MyGlWindow::MyGlWindow() {

}
MyGlWindow::~MyGlWindow() {

}
void MyGlWindow::MoveMouse(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    LastCursorPos = glm::vec2(xpos, ypos); 
}
void MyGlWindow::ResizeWindow(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
void MyGlWindow::ClickMouse(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        lastClickPos.push_back(LastCursorPos);
    }
}
bool MyGlWindow::GetLastClickPos(glm::vec2 &lastClick) {
    if (lastClickPos.empty()) {
        return false;
    } else {
        lastClick = lastClickPos.back();
        lastClickPos.clear();
        return true;
    }
}