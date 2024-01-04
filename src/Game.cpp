#include "Game.h"
#include "Renderer2D.h"
#include "Board.h"
#include <cmath>

Game::Game() {
    try {
        board    = std::make_unique<Board>();
        renderer = std::make_unique<Renderer2D>();
    } catch (std::exception &e) {
        std::cerr << "Game Initialization Error: " << e.what() << std::endl;
    }
    renderer->UpdateBoardState  ("rnbqkb-rpppppppp-----n--------------------------PPP-PPPPRNBQKBNR");
    renderer->ShowPreviousMove  ("------m--------------m------------------------------------------");
}
Game::~Game() {

}
void Game::ExecuteFrame() {
    renderer->PrepareFrame();
    renderer->ProcessInput();
    // insert game logic here
    processClicks();
    renderer->RenderFrame();
    renderer->EndFrame();
}
bool Game::IsRunning() {
    return renderer->IsRunning();
}
void Game::processClicks() {
    uint64_t bitSquareClicked;
    if (!renderer->GetLastSquareClicked(bitSquareClicked)) {
        return;
    }
    std::string stringBoard = "----------------------------------------------------------------";
    size_t index = static_cast<size_t>(std::abs(std::log2l(static_cast<long double>(bitSquareClicked)) - 63));
    stringBoard.at(index) = 'c';
    renderer->ShowAvailableMoves(stringBoard);
    
}