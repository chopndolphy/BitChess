#include "Renderer2D.h"
#include "ResourceManager.h"

#include <filesystem>

Renderer2D::Renderer2D() {
    initWindow();
    initOpenGL();
    initShadersAndTextures();
}
Renderer2D::~Renderer2D() {
    glfwTerminate();
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
    for (auto uiElement = uiElements.begin(); uiElement != uiElements.end(); uiElement++) {
        uiElement->second->Draw();
    }
    for (auto &piece : pieces) {
        piece->Draw(); 
    }
}
void Renderer2D::EndFrame() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}
bool Renderer2D::IsRunning() {
    return !glfwWindowShouldClose(window);
}
void Renderer2D::UpdateBoardState(std::string boardState) {
    pieces.clear(); //some way to not have to clear every update and just update changed ones?
    for (size_t i = 0; i < boardState.length(); i++) {
        switch (boardState[i]) { // could also use inheritance
            case 'K':
                // pieces.emplace_back(Sprite(/*shader, texCoord in map, position (need coord converter), size (set default size for piece)*/))
                break;
            case 'k':

                break;
            case 'Q':

                break;
            case 'q':
                
                break;
            case 'R':

                break;
            case 'r':

                break;
            case 'B':

                break;
            case 'b':

                break;
            case 'N':

                break;
            case 'n':

                break;
            case 'P':

                break;
            case 'p':

                break;
        }
    }
}
void Renderer2D::initWindow() {
    myWindow = std::make_shared<MyGlWindow>();
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

    glfwSetWindowUserPointer(window, myWindow.get());
    auto resizeFunc = [](GLFWwindow* w, int width, int height) {
        static_cast<MyGlWindow*>(glfwGetWindowUserPointer(w))->ResizeWindow(w, width, height);
    };
    glfwSetFramebufferSizeCallback(window, resizeFunc);
    auto mouseMoveFunc = [](GLFWwindow* w, double xposIn, double yposIn) {
        static_cast<MyGlWindow*>(glfwGetWindowUserPointer(w))->MoveMouse(w, xposIn, yposIn);
    };
    glfwSetCursorPosCallback(window, mouseMoveFunc);
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
void Renderer2D::initShadersAndTextures() {
    std::filesystem::path shaderAbsPath = std::filesystem::absolute("./shaders/");
    std::filesystem::path textureAbsPath = std::filesystem::absolute("./textures/");
    ResourceManager::LoadShader((shaderAbsPath / "sprite.vert").string().c_str(), (shaderAbsPath / "sprite.frag").string().c_str(), nullptr, "sprite");
    ResourceManager::GetShader("sprite").lock()->activate_shader().setInt("image", 0);
    ResourceManager::GetShader("sprite").lock()->setMat4("projection", projection);
    uiElements.try_emplace("board", std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), glm::vec4(0.5f, 0.0f, 1.0f, 0.5f), glm::vec2(static_cast<float>(myWindow->SCR_WIDTH / 5), static_cast<float>(myWindow->SCR_HEIGHT / 10)), glm::vec2(static_cast<float>((3 * myWindow->SCR_WIDTH) / 5), static_cast<float>((3 * myWindow->SCR_WIDTH) / 5))));
    glActiveTexture(GL_TEXTURE0);
    ResourceManager::LoadTexture((textureAbsPath / "chess.png").string().c_str(), true, "chess").lock()->Bind();
}