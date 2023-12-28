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
        Renderer2D* renderer;

};