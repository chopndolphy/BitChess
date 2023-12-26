#include "Game.h"

Game::Game() {
    try {
        renderer = std::make_unique<Renderer2D>();
    } catch (std::exception &e) {
        std::cerr << "Game Initialization Error: " << e.what() << std::endl;
    }
}
Game::~Game() {

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