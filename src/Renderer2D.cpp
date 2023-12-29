#include "Renderer2D.h"
#include "MyGlWindow.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "Texture2D.h"

#include <filesystem>

Renderer2D::Renderer2D() {
    initWindow();
    initOpenGL();
    initSprites();
}
Renderer2D::~Renderer2D() {
    glfwTerminate();
    delete myWindow;
}
void Renderer2D::PrepareFrame() {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}
void Renderer2D::ProcessInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
void Renderer2D::RenderFrame() {
    glClear(GL_COLOR_BUFFER_BIT);
    Texture2D &board = ResourceManager::GetTexture("chess"); //move somewhere else
    spriteRenderer->DrawSprite(board, glm::vec2(static_cast<float>(myWindow->SCR_WIDTH / 5), static_cast<float>(myWindow->SCR_HEIGHT / 10)), glm::vec2(static_cast<float>((3 * myWindow->SCR_WIDTH) / 5), static_cast<float>((3 * myWindow->SCR_WIDTH) / 5)));
}
void Renderer2D::EndFrame() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}
bool Renderer2D::IsRunning() {
    return !glfwWindowShouldClose(window);
}
void Renderer2D::initOpenGL() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    glViewport(0, 0, myWindow->SCR_WIDTH, myWindow->SCR_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
    projection = glm::ortho(0.0f, static_cast<float>(myWindow->SCR_WIDTH), static_cast<float>(myWindow->SCR_HEIGHT), 0.0f, -1.0f, 1.0f);
}
void Renderer2D::initWindow() {
    myWindow = new MyGlWindow;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);
    
    window = glfwCreateWindow(myWindow->SCR_WIDTH, myWindow->SCR_HEIGHT, "Chess", NULL, NULL);
    if (!window) {
        throw std::runtime_error("Failed to create GLFW window");
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    glfwSetWindowUserPointer(window, myWindow);
    auto resizeFunc = [](GLFWwindow* w, int width, int height) {
        static_cast<MyGlWindow*>(glfwGetWindowUserPointer(w))->ResizeWindow(w, width, height);
    };
    glfwSetFramebufferSizeCallback(window, resizeFunc);
    auto mouseMoveFunc = [](GLFWwindow* w, double xposIn, double yposIn) {
        static_cast<MyGlWindow*>(glfwGetWindowUserPointer(w))->MoveMouse(w, xposIn, yposIn);
    };
    glfwSetCursorPosCallback(window, mouseMoveFunc);
}
void Renderer2D::initSprites() {
    std::filesystem::path shaderAbsPath = std::filesystem::absolute("./shaders/");
    std::filesystem::path textureAbsPath = std::filesystem::absolute("./textures/");
    ResourceManager::LoadShader((shaderAbsPath / "sprite.vert").string().c_str(), (shaderAbsPath / "sprite.frag").string().c_str(), nullptr, "sprite");
    ResourceManager::GetShader("sprite").activate_shader().setInt("image", 0);
    ResourceManager::GetShader("sprite").setMat4("projection", projection);
    spriteRenderer = new Sprite(ResourceManager::GetShader("sprite"), glm::vec4(0.5f, 0.0f, 1.0f, 0.5f));
    ResourceManager::LoadTexture((textureAbsPath / "chess.png").string().c_str(), true, "chess");
}