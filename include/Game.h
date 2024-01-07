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
        void SetState(const GameState &newState);
        void ShutDown();
        const GameState& GetCurrentState();
        std::weak_ptr<Renderer2D> GetRenderer();
    private:
        GameState& currentState;
        std::shared_ptr<Renderer2D> renderer;
        std::unique_ptr<Board> board;
        void processClicks();
};