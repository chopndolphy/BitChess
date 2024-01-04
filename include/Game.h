#pragma once

#include <memory>

class Renderer2D;
class Board;

class Game {
    public:
        Game();
        ~Game();
        void ExecuteFrame();
        bool IsRunning();
    private:
        std::unique_ptr<Renderer2D> renderer;
        std::unique_ptr<Board> board;
        void processClicks();
};