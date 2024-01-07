#include "Renderer2D.h"
#include "ResourceManager.h"

#include <filesystem>
#include <iostream>

Renderer2D::Renderer2D() {
    initWindow();
    initOpenGL();
    initShadersAndTextures();
    initUIElements();
    initCursor();
}
Renderer2D::~Renderer2D() {
    destroySprites();
    ResourceManager::Clear();
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
    glm::vec2 lastClickPos;
    if (myWindow->GetLastClickPos(lastClickPos)) {
        if (lastClickPos.x > boardOffset.x && lastClickPos.x < (boardOffset.x + boardSize.x) && 
            lastClickPos.y > boardOffset.y && lastClickPos.y < (boardOffset.y + boardSize.y)) { // lastClickPos on board

            lastSquareClicked = std::make_unique<uint64_t>(Util::IndexToBitBoard(Util::PositionToIndex(lastClickPos, squareSize, boardOffset)));
        }

    } 
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
    if (chosenPieceSprite != nullptr) {
        chosenPieceSprite->Draw();
    }
    glm::vec2 cursorPos = myWindow->LastCursorPos;
    if (!availableMovesSprites.empty()) {
        for (auto &highlight : availableMovesSprites) {
            if (highlight->position.x <= cursorPos.x && highlight->position.x + squareSize.x >= cursorPos.x && 
                highlight->position.y <= cursorPos.y && highlight->position.y + squareSize.y >= cursorPos.y) { // cursor over square
            
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
                
                pieceSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.125f, 0.0f, 0.1875f, 0.0625f), Util::IndexToPosition(i, squareSize, boardOffset), squareSize));
                break;
            case 'p':
                pieceSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.125f, 0.0625f, 0.1875f, 0.125f), Util::IndexToPosition(i, squareSize, boardOffset), squareSize));
                break;
            case 'K':
                pieceSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.1875f, 0.0f, 0.25f, 0.0625f), Util::IndexToPosition(i, squareSize, boardOffset), squareSize));
                break;
            case 'k':
                pieceSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.1875f, 0.0625f, 0.25f, 0.125f), Util::IndexToPosition(i, squareSize, boardOffset), squareSize));
                break;
            case 'Q':
                pieceSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.25f, 0.0f, 0.3125f, 0.0625f), Util::IndexToPosition(i, squareSize, boardOffset), squareSize));
                break;
            case 'q':
                pieceSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.25f, 0.0625f, 0.3125f, 0.125f), Util::IndexToPosition(i, squareSize, boardOffset), squareSize));
                break;
            case 'B':
                pieceSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.3125f, 0.0f, 0.375f, 0.0625f), Util::IndexToPosition(i, squareSize, boardOffset), squareSize));
                break;
            case 'b':
                pieceSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.3125f, 0.0625f, 0.375f, 0.125f), Util::IndexToPosition(i, squareSize, boardOffset), squareSize));
                break;
            case 'N':
                pieceSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.375f, 0.0f, 0.4375f, 0.0625f), Util::IndexToPosition(i, squareSize, boardOffset), squareSize));
                break;
            case 'n':
                pieceSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.375f, 0.0625f, 0.4375f, 0.125f), Util::IndexToPosition(i, squareSize, boardOffset), squareSize));
                break;
            case 'R':
                pieceSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.4375f, 0.0f, 0.5f, 0.0625f), Util::IndexToPosition(i, squareSize, boardOffset), squareSize));
                break;
            case 'r':
                pieceSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.4375f, 0.0625f, 0.5f, 0.125f), Util::IndexToPosition(i, squareSize, boardOffset), squareSize));
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
                availableMovesSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("hoverable"), 
                    glm::vec4(0.0f, 0.0625f, 0.0625f, 0.125f), Util::IndexToPosition(i, squareSize, boardOffset), squareSize));
                break;
            case 'm':
                availableMovesSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("hoverable"), 
                    glm::vec4(0.0625f, 0.0625f, 0.125f, 0.125f), Util::IndexToPosition(i, squareSize, boardOffset), squareSize));
                break;
            case 'c':
                chosenPieceSprite = std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.0f, 0.0f, 0.0625f, 0.0625f), Util::IndexToPosition(i, squareSize, boardOffset), squareSize);
            default:
                break;
        }
    }
}
void Renderer2D::ShowPreviousMove(std::string previousMove) {
    previousMoveSprites.clear();
    for (size_t i = 0; i < previousMove.length(); i++) {
        if (previousMove[i] == 'm') {
            previousMoveSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                glm::vec4(0.0625f, 0.0f, 0.125f, 0.0625f), Util::IndexToPosition(i, squareSize, boardOffset), squareSize));
        }
    }
}
bool Renderer2D::GetLastSquareClicked(uint64_t &bitSquareClicked) {
    if (!lastSquareClicked) {
        return false;
    } else {
        bitSquareClicked = *lastSquareClicked.get();
        lastSquareClicked.reset();
        return true;
    }
}
void Renderer2D::initWindow() {
    myWindow = std::make_shared<MyGlWindow>();
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    window = glfwCreateWindow(myWindow->SCR_WIDTH, myWindow->SCR_HEIGHT, "Chess", NULL, NULL);
    if (!window) {
        throw std::runtime_error("Failed to create GLFW window");
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, myWindow.get());
    
    auto mouseMoveFunc = [](GLFWwindow* w, double xposIn, double yposIn) {
        static_cast<MyGlWindow*>(glfwGetWindowUserPointer(w))->MoveMouse(w, xposIn, yposIn);
    };
    glfwSetCursorPosCallback(window, mouseMoveFunc);

    auto mouseClickFunc = [](GLFWwindow* w, int button, int action, int mods) {
        static_cast<MyGlWindow*>(glfwGetWindowUserPointer(w))->ClickMouse(w, button, action, mods);
    };
    glfwSetMouseButtonCallback(window, mouseClickFunc);
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
    std::filesystem::path fileAbsPath = std::filesystem::absolute(__FILE__);
    std::filesystem::path shaderAbsPath = std::filesystem::absolute(fileAbsPath.parent_path().parent_path() / "shaders/");
    std::filesystem::path textureAbsPath = std::filesystem::absolute(fileAbsPath.parent_path().parent_path() / "textures/");
    std::cout << shaderAbsPath << std::endl << textureAbsPath << std::endl;
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
void Renderer2D::initCursor() {
    GLFWimage image;
    std::filesystem::path fileAbsPath = std::filesystem::absolute(__FILE__);
    std::filesystem::path cursorAbsPath = std::filesystem::absolute(fileAbsPath.parent_path().parent_path() / "textures/");
    image.pixels = stbi_load((cursorAbsPath / "chess_cursor.png").string().c_str(), &image.width, &image.height, 0, 4);
    cursor = glfwCreateCursor(&image, 0, 0);
    glfwSetCursor(window, cursor);
    stbi_image_free(image.pixels);
}
void Renderer2D::destroySprites() {
    staticSprites.clear();
    pieceSprites.clear();
    availableMovesSprites.clear();
    chosenPieceSprite.reset();
    previousMoveSprites.clear();
}