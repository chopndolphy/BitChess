#include "Game.h"
#include "Renderer2D.h"
#include "Board.h"
#include "GameState.h"
#include "BlackSelectingMoveState.h"
#include "BlackSelectingPieceState.h"
#include "WhiteSelectingMoveState.h"
#include "WhiteSelectingPieceState.h"
#include <cmath>

Game::Game() {
    currentState = &WhiteSelectingPieceState::GetInstance();
    try {
        board    = std::make_unique<Board>();
        renderer = std::make_unique<Renderer2D>();
    } catch (std::exception &e) {
        std::cerr << "Game Initialization Error: " << e.what() << std::endl;
    }
    renderer->UpdateBoardState("rnbqkbnrpppppppp--------------------------------PPPPPPPPRNBQKBNR");
}
Game::~Game() {

}
void Game::ExecuteFrame() {
    renderer->PrepareFrame();
    renderer->ProcessInput();
    processClicks();
    renderer->RenderFrame();
    renderer->EndFrame();
}
bool Game::IsRunning() {
    return renderer->IsRunning();
}
void Game::SetState(GameState &newState){
    currentState->Exit(Me());
    currentState = &newState;
    currentState->Enter(Me());
}
void Game::SetSelectedPiece(uint64_t selectedPiece) {
    this->selectedPiece = selectedPiece;
}
uint64_t Game::GetSelectedPiece() {
    return selectedPiece;
}
void Game::ShutDown(){
    board.reset();
    renderer.reset();
}
const GameState &Game::GetCurrentState() {
    return *currentState;
}
std::weak_ptr<Renderer2D> Game::GetRenderer() {
    return renderer;
}
std::weak_ptr<Board> Game::GetBoard() {
    return board;
}
void Game::processClicks() {
    currentState->ProcessClicks(Me());
}