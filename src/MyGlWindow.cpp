#include "MyGlWindow.h"

MyGlWindow::MyGlWindow() {

}
MyGlWindow::~MyGlWindow() {

}
void MyGlWindow::MoveMouse(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    lastCursorPos = glm::vec2(xpos, ypos); 
}
void MyGlWindow::ResizeWindow(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
void MyGlWindow::ClickMouse(GLFWwindow* window, int button, int action, int mods) {

}