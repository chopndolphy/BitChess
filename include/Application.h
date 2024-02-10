#pragma once
#include <memory>
#include "Renderer2D.h"
#include "Enums.h"
class Position;
class AppState;
class StartState;
class WhiteSelectingPieceState;
class WhiteSelectingMoveState;
class WhitePromotingPawnState;
class BlackSelectingPieceState;
class BlackSelectingMoveState;
class BlackPromotingPawnState;
class EndState;

class Application {
    public:
        Application();
        ~Application();
        Application& Me() & { return *this; }
        Application& Me() && = delete;
        void ExecuteFrame();
        void ShutDown();
        void CurrentState(std::weak_ptr<AppState> newState);
        std::weak_ptr<AppState> CurrentState() {
            return currentState;
        }
        bool IsRunning() {
            return renderer->IsRunning();
        }
        void SelectedPiece(uint64_t selectedPiece) {
            this->selectedPiece = selectedPiece;
        }
        uint64_t SelectedPiece() {
            return selectedPiece;
        }
        void PromotionSquare(uint64_t promotionSquare) {
            this->promotionSquare = promotionSquare;
        }
        uint64_t PromotionSquare() {
            return promotionSquare;
        }
        std::weak_ptr<Renderer2D> Renderer() {
            return renderer;
        }
        std::weak_ptr<Position> Board() {
            return board;
        }
        const std::weak_ptr<StartState> Start() {
            return startState;
        }
        const std::weak_ptr<WhiteSelectingPieceState> WhiteSelectingPiece() {
            return whiteSelectingPieceState;
        }
        const std::weak_ptr<WhiteSelectingMoveState> WhiteSelectingMove() {
            return whiteSelectingMoveState;
        }
        const std::weak_ptr<WhitePromotingPawnState> WhitePromotingPawn() {
            return whitePromotingPawnState;
        }
        const std::weak_ptr<BlackSelectingPieceState> BlackSelectingPiece() {
            return blackSelectingPieceState;
        }
        const std::weak_ptr<BlackSelectingMoveState> BlackSelectingMove() {
            return blackSelectingMoveState;
        }
        const std::weak_ptr<BlackPromotingPawnState> BlackPromotingPawn() {
            return blackPromotingPawnState;
        }
        const std::weak_ptr<EndState> End() {
            return endState;
        }
        EndDisplay AppEndDisplay;
    private:
        std::weak_ptr<AppState> currentState;
        std::shared_ptr<StartState> startState;
        std::shared_ptr<WhiteSelectingPieceState> whiteSelectingPieceState;
        std::shared_ptr<WhiteSelectingMoveState> whiteSelectingMoveState;
        std::shared_ptr<WhitePromotingPawnState> whitePromotingPawnState;
        std::shared_ptr<BlackSelectingPieceState> blackSelectingPieceState;
        std::shared_ptr<BlackSelectingMoveState> blackSelectingMoveState;
        std::shared_ptr<BlackPromotingPawnState> blackPromotingPawnState;
        std::shared_ptr<EndState> endState;
        std::shared_ptr<Renderer2D> renderer;
        std::shared_ptr<Position> board;
        uint64_t selectedPiece;
        uint64_t promotionSquare;
        void processClicks();
};