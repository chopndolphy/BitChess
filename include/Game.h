#pragma once


#include <memory>

class Renderer2D;
class Board;
class GameState;

class Game {
    public:
        Game();
        ~Game();
        Game& Me() & { return *this; }
        Game& Me() && = delete;
        void ExecuteFrame();
        bool IsRunning();
        void SetState(GameState &newState);
        void SetSelectedPiece(uint64_t selectedPiece);
        uint64_t GetSelectedPiece();
        void ShutDown();
        const GameState& GetCurrentState();
        std::weak_ptr<Renderer2D> GetRenderer();
        std::weak_ptr<Board> GetBoard();
    private:
        GameState* currentState;
        std::shared_ptr<Renderer2D> renderer;
        std::shared_ptr<Board> board;
        void processClicks();
        uint64_t selectedPiece;
};