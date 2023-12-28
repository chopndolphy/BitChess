#pragma once

#include <memory>

class Renderer2D;

class Game {
    public:
        Game();
        ~Game();
        void ExecuteFrame();
        bool IsRunning();
    private:
        std::unique_ptr<Renderer2D> renderer;

};