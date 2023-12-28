#include "MyGlWindow.h"

MyGlWindow::MyGlWindow() {
    
}
void MyGlWindow::MoveMouse(GLFWwindow* window, double xposIn, double yposIn) {
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
void MyGlWindow::ResizeWindow(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}