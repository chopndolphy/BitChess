#include "MyGlWindow.h"

MyGlWindow::MyGlWindow() {

}
MyGlWindow::~MyGlWindow() {

}
void MyGlWindow::MoveMouse(GLFWwindow* window, double xposIn, double yposIn) {
    LastCursorPos = glm::vec2(static_cast<float>(xposIn), static_cast<float>(yposIn)); 
}
void MyGlWindow::ClickMouse(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        lastClickPos = std::make_unique<glm::vec2>(LastCursorPos);
    }
}
bool MyGlWindow::GetLastClickPos(glm::vec2 &lastClick) {
    if (!lastClickPos) {
        return false;
    } else {
        lastClick = *lastClickPos.get();
        lastClickPos.reset();
        return true;
    }
}