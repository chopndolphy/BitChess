#include "Game.h"
#include "Renderer2D.h"

Game::Game() {
    try {
        renderer = new Renderer2D;
    } catch (std::exception &e) {
        std::cerr << "Game Initialization Error: " << e.what() << std::endl;
    }
}
Game::~Game() {
    delete renderer;
}
void Game::ExecuteFrame() {
    renderer->PrepareFrame();
    renderer->ProcessInput();
    // insert game logic here
    renderer->RenderFrame();
    renderer->EndFrame();
}
bool Game::IsRunning() {
    return renderer->IsRunning();
}