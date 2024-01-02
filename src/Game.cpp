#include "Game.h"
#include "Renderer2D.h"
#include "Board.h"

Game::Game() {
    try {
        board    = std::make_unique<Board>();
        renderer = std::make_unique<Renderer2D>();
    } catch (std::exception &e) {
        std::cerr << "Game Initialization Error: " << e.what() << std::endl;
    }
    renderer->UpdateBoardState  ("rnbqkb-rpppppppp-----n--------------------------PPP-PPPPRNBQKBNR");
    renderer->ShowAvailableMoves("-----------a-------m-------m-------m-------m-------m-------c----");
    renderer->ShowPreviousMove  ("------m--------------m------------------------------------------");
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