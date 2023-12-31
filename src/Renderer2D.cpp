#include "Renderer2D.h"
#include "ResourceManager.h"

#include <filesystem>

Renderer2D::Renderer2D() {
    initWindow();
    initOpenGL();
    initShadersAndTextures();
    initUIElements();
    UpdateBoardState  ("rnbqkb-rpppppppp-----n--------------------------PPP-PPPPRNBQKBNR");
    ShowAvailableMoves("-----------a-------m-------m-------m-------m-------m-------c----");
    ShowPreviousMove  ("------m--------------m------------------------------------------");
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
    if (!staticSprites.empty()) {
        for (auto sprite = staticSprites.begin(); sprite != staticSprites.end(); sprite++) {
            sprite->second->Draw();
        }
    }
    if (!previousMoveSprites.empty()) {
        for (auto &highlight : previousMoveSprites) {
            highlight->Draw();
        }
    }
    chosenPieceSprite->Draw();
    glm::vec2 cursorPos = myWindow->lastCursorPos;
    if (!availableMovesSprites.empty()) {
        for (auto &highlight : availableMovesSprites) {
            if (highlight->position.x <= cursorPos.x && highlight->position.x + squareSize.x >= cursorPos.x && 
                highlight->position.y <= cursorPos.y && highlight->position.y + squareSize.y >= cursorPos.y) {
            
                highlight->setHovering(true);
            } else {
                highlight->setHovering(false);     
            }
            highlight->Draw();
        }
    }
    if (!pieceSprites.empty()) {
        for (auto &piece : pieceSprites) {
            piece->Draw(); 
        }
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
    pieceSprites.clear();
    for (size_t i = 0; i < boardState.length(); i++) {
        switch (boardState[i]) {
            case 'P':
                pieceSprites.emplace_back(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.125f, 0.0f, 0.1875f, 0.0625f), indexToPosition(i), squareSize));
                break;
            case 'p':
                pieceSprites.emplace_back(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.125f, 0.0625f, 0.1875f, 0.125f), indexToPosition(i), squareSize));
                break;
            case 'K':
                pieceSprites.emplace_back(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.1875f, 0.0f, 0.25f, 0.0625f), indexToPosition(i), squareSize));
                break;
            case 'k':
                pieceSprites.emplace_back(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.1875f, 0.0625f, 0.25f, 0.125f), indexToPosition(i), squareSize));
                break;
            case 'Q':
                pieceSprites.emplace_back(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.25f, 0.0f, 0.3125f, 0.0625f), indexToPosition(i), squareSize));
                break;
            case 'q':
                pieceSprites.emplace_back(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.25f, 0.0625f, 0.3125f, 0.125f), indexToPosition(i), squareSize));
                break;
            case 'B':
                pieceSprites.emplace_back(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.3125f, 0.0f, 0.375f, 0.0625f), indexToPosition(i), squareSize));
                break;
            case 'b':
                pieceSprites.emplace_back(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.3125f, 0.0625f, 0.375f, 0.125f), indexToPosition(i), squareSize));
                break;
            case 'N':
                pieceSprites.emplace_back(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.375f, 0.0f, 0.4375f, 0.0625f), indexToPosition(i), squareSize));
                break;
            case 'n':
                pieceSprites.emplace_back(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.375f, 0.0625f, 0.4375f, 0.125f), indexToPosition(i), squareSize));
                break;
            case 'R':
                pieceSprites.emplace_back(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.4375f, 0.0f, 0.5f, 0.0625f), indexToPosition(i), squareSize));
                break;
            case 'r':
                pieceSprites.emplace_back(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.4375f, 0.0625f, 0.5f, 0.125f), indexToPosition(i), squareSize));
                break;
            default:
                break;
        }
    }
}
void Renderer2D::ShowAvailableMoves(std::string availableMoves) {
    availableMovesSprites.clear();
    chosenPieceSprite.reset();
    for (size_t i = 0; i < availableMoves.length(); i++) {
        switch (availableMoves[i]) {
            case 'a':
                availableMovesSprites.emplace_back(std::make_unique<Sprite>(ResourceManager::GetShader("hoverable"), 
                    glm::vec4(0.0f, 0.0625f, 0.0625f, 0.125f), indexToPosition(i), squareSize));
                break;
            case 'm':
                availableMovesSprites.emplace_back(std::make_unique<Sprite>(ResourceManager::GetShader("hoverable"), 
                    glm::vec4(0.0625f, 0.0625f, 0.125f, 0.125f), indexToPosition(i), squareSize));
                break;
            case 'c':
                chosenPieceSprite = std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.0f, 0.0f, 0.0625f, 0.0625f), indexToPosition(i), squareSize);
            default:
                break;
        }
    }
}
void Renderer2D::ShowPreviousMove(std::string previousMove) {
    previousMoveSprites.clear();
    for (size_t i = 0; i < previousMove.length(); i++) {
        if (previousMove[i] == 'm') {
            previousMoveSprites.emplace_back(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                glm::vec4(0.0625f, 0.0f, 0.125f, 0.0625f), indexToPosition(i), squareSize));
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
    ResourceManager::LoadShader((shaderAbsPath / "hoverable.vert").string().c_str(), (shaderAbsPath / "hoverable.frag").string().c_str(), nullptr, "hoverable");
    ResourceManager::GetShader("hoverable").lock()->activate_shader().setInt("image", 0);
    ResourceManager::GetShader("hoverable").lock()->setMat4("projection", projection);
    ResourceManager::GetShader("hoverable").lock()->setBool("hoverOver", false);
    glActiveTexture(GL_TEXTURE0);
    ResourceManager::LoadTexture((textureAbsPath / "chess.png").string().c_str(), true, "chess").lock()->Bind();
}
void Renderer2D::initUIElements() {
    boardOffset = glm::vec2((0.2f * myWindow->SCR_WIDTH), (0.1f * myWindow->SCR_HEIGHT));
    boardSize = glm::vec2((0.6f * myWindow->SCR_WIDTH), 0.6f * myWindow->SCR_WIDTH);
    staticSprites.try_emplace("board", std::make_unique<Sprite>(
        ResourceManager::GetShader("sprite"), 
        glm::vec4(0.5f, 0.0f, 1.0f, 0.5f), 
        glm::vec2(boardOffset), 
        glm::vec2(boardSize)));
    squareSize = glm::vec2((0.125f * boardSize.x), (0.125f * boardSize.y));
}
glm::vec2 Renderer2D::indexToPosition(size_t boardIndex) { // calculates screen coordinate for a board position based on index
    float posX = (boardOffset.x + ((0.125f * boardSize.x) * (static_cast<float>(boardIndex % 8))));
    float posY = (boardOffset.y + ((0.125f * boardSize.y) * (std::floor(static_cast<float>(boardIndex / 8)))));
    return glm::vec2(posX, posY);
}