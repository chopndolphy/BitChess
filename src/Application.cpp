#include "Application.h"
#include "AppState.h"
#include "StartState.h"
#include "WhiteSelectingPieceState.h"
#include "WhiteSelectingMoveState.h"
#include "BlackSelectingPieceState.h"
#include "BlackSelectingMoveState.h"
#include "EndState.h"
#include "Renderer2D.h"
#include "Position.h"


Application::Application() {
    try {
        board = std::make_unique<Position>();
        renderer = std::make_unique<Renderer2D>();
        startState = std::make_shared<StartState>(Me());
        whiteSelectingPieceState = std::make_shared<WhiteSelectingPieceState>(Me()); 
        whiteSelectingMoveState = std::make_shared<WhiteSelectingMoveState>(Me());
        blackSelectingPieceState = std::make_shared<BlackSelectingPieceState>(Me());
        blackSelectingMoveState = std::make_shared<BlackSelectingMoveState>(Me());
        endState = std::make_shared<EndState>(Me());
        currentState = whiteSelectingPieceState;
    } catch (std::exception &e) {
        std::cerr << "Game Initialization Error: " << e.what() << std::endl;
    }
    renderer->UpdateBoardState("rnbqkbnrpppppppp--------------------------------PPPPPPPPRNBQKBNR");
}
Application::~Application() {

}
void Application::ExecuteFrame() {
    renderer->PrepareFrame();
    renderer->ProcessInput();
    processClicks();
    renderer->RenderFrame();
    renderer->EndFrame();
}
void Application::CurrentState(std::weak_ptr<AppState> newState){
    currentState.lock()->Exit();
    currentState = newState;
    currentState.lock()->Enter();
}
void Application::ShutDown(){
    board.reset();
    renderer.reset();
}
void Application::processClicks() {
    currentState.lock()->ProcessClicks();
}