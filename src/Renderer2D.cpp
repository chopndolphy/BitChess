#include "Renderer2D.h"
#include "ResourceManager.h"

#include <filesystem>

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
        if (lastClickPos.x > myWindow->BoardOffset.x && lastClickPos.x < (myWindow->BoardOffset.x + myWindow->BoardSize.x) && 
            lastClickPos.y > myWindow->BoardOffset.y && lastClickPos.y < (myWindow->BoardOffset.y + myWindow->BoardSize.y)) { // lastClickPos on board

            lastSquareClicked = std::make_unique<uint64_t>(Util::IndexToBitBoard(Util::PositionToIndex(lastClickPos, myWindow->SquareSize, myWindow->BoardOffset)));
        }

    } 
}
void Renderer2D::RenderFrame() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (!staticSprites.empty()) {
        for (auto sprite = staticSprites.begin(); sprite != staticSprites.end(); sprite++) {
            sprite->second->Draw(myWindow->Projection, myWindow->BoardOffset, myWindow->BoardSize);
        }
    }
    if (!previousMoveSprites.empty()) {
        for (auto &highlight : previousMoveSprites) {
            highlight->Draw(myWindow->Projection, Util::IndexToPosition(highlight->BoardLocation, myWindow->SquareSize, myWindow->BoardOffset), myWindow->SquareSize);
        }
    }
    if (chosenPieceSprite != nullptr) {
        chosenPieceSprite->Draw(myWindow->Projection, Util::IndexToPosition(chosenPieceSprite->BoardLocation, myWindow->SquareSize, myWindow->BoardOffset), myWindow->SquareSize);
    }
    glm::vec2 cursorPos = myWindow->LastCursorPos;
    uint64_t lastSquareHovered = 0;
    if (cursorPos.x > myWindow->BoardOffset.x && cursorPos.x < (myWindow->BoardOffset.x + myWindow->BoardSize.x) && 
        cursorPos.y > myWindow->BoardOffset.y && cursorPos.y < (myWindow->BoardOffset.y + myWindow->BoardSize.y)) { // lastClickPos on board

            lastSquareHovered = Util::IndexToBitBoard(Util::PositionToIndex(cursorPos, myWindow->SquareSize, myWindow->BoardOffset));
        }
    if (!availableMovesSprites.empty()) {
        for (auto &highlight : availableMovesSprites) {
            if (lastSquareHovered & Util::IndexToBitBoard(highlight->BoardLocation)) { // cursor over square
            
                highlight->setHovering(true);
            } else {
                highlight->setHovering(false);     
            }
            highlight->Draw(myWindow->Projection, Util::IndexToPosition(highlight->BoardLocation, myWindow->SquareSize, myWindow->BoardOffset), myWindow->SquareSize);
        }
    }
    if (!pieceSprites.empty()) {
        for (auto &piece : pieceSprites) {
            piece->Draw(myWindow->Projection, Util::IndexToPosition(piece->BoardLocation, myWindow->SquareSize, myWindow->BoardOffset), myWindow->SquareSize);

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
                    glm::vec4(0.125f, 0.0f, 0.1875f, 0.0625f), i));
                break;
            case 'p':
                pieceSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.125f, 0.0625f, 0.1875f, 0.125f), i));
                break;
            case 'K':
                pieceSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.1875f, 0.0f, 0.25f, 0.0625f), i));
                break;
            case 'k':
                pieceSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.1875f, 0.0625f, 0.25f, 0.125f), i));
                break;
            case 'Q':
                pieceSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.25f, 0.0f, 0.3125f, 0.0625f), i));
                break;
            case 'q':
                pieceSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.25f, 0.0625f, 0.3125f, 0.125f), i));
                break;
            case 'B':
                pieceSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.3125f, 0.0f, 0.375f, 0.0625f), i));
                break;
            case 'b':
                pieceSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.3125f, 0.0625f, 0.375f, 0.125f), i));
                break;
            case 'N':
                pieceSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.375f, 0.0f, 0.4375f, 0.0625f), i));
                break;
            case 'n':
                pieceSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.375f, 0.0625f, 0.4375f, 0.125f), i));
                break;
            case 'R':
                pieceSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.4375f, 0.0f, 0.5f, 0.0625f), i));
                break;
            case 'r':
                pieceSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.4375f, 0.0625f, 0.5f, 0.125f), i));
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
                    glm::vec4(0.0f, 0.0625f, 0.0625f, 0.125f), i));
                break;
            case 'm':
                availableMovesSprites.emplace(std::make_unique<Sprite>(ResourceManager::GetShader("hoverable"), 
                    glm::vec4(0.0625f, 0.0625f, 0.125f, 0.125f), i));
                break;
            case 'c':
                chosenPieceSprite = std::make_unique<Sprite>(ResourceManager::GetShader("sprite"), 
                    glm::vec4(0.0f, 0.0f, 0.0625f, 0.0625f), i);
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
                glm::vec4(0.0625f, 0.0f, 0.125f, 0.0625f), i ));
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
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    // glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

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

    auto resizeWindowFunc = [](GLFWwindow* w, int width, int height) {
        static_cast<MyGlWindow*>(glfwGetWindowUserPointer(w))->ResizeWindow(w, width, height);
        
    };
    glfwSetFramebufferSizeCallback(window, resizeWindowFunc);

    glfwSetWindowAspectRatio(window, myWindow->SCR_WIDTH, myWindow->SCR_HEIGHT);
}
void Renderer2D::initOpenGL() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    glViewport(0, 0, myWindow->SCR_WIDTH, myWindow->SCR_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
}
void Renderer2D::initShadersAndTextures() {
    std::filesystem::path shaderAbsPath = Util::AbsProjectDirectory().append("shaders/");
    std::filesystem::path textureAbsPath = Util::AbsProjectDirectory().append("textures/");
    ResourceManager::LoadShader((shaderAbsPath / "sprite.vert").string().c_str(), (shaderAbsPath / "sprite.frag").string().c_str(), nullptr, "sprite");
    ResourceManager::GetShader("sprite").lock()->activate_shader().setInt("image", 0);
    ResourceManager::LoadShader((shaderAbsPath / "hoverable.vert").string().c_str(), (shaderAbsPath / "hoverable.frag").string().c_str(), nullptr, "hoverable");
    ResourceManager::GetShader("hoverable").lock()->activate_shader().setInt("image", 0);
    ResourceManager::GetShader("hoverable").lock()->setBool("hoverOver", false);
    glActiveTexture(GL_TEXTURE0);
    ResourceManager::LoadTexture((textureAbsPath / "chess.png").string().c_str(), true, "chess").lock()->Bind();
}
void Renderer2D::initUIElements() {
    staticSprites.try_emplace("board", std::make_unique<Sprite>(
        ResourceManager::GetShader("sprite"), 
        glm::vec4(0.5f, 0.0f, 1.0f, 0.5f)));
}
void Renderer2D::initCursor() {
    std::filesystem::path cursorAbsPath = Util::AbsProjectDirectory().append("textures/");
    GLFWimage image;
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