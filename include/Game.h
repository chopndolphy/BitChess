#pragma once
#include "Renderer2D.h"

#include <memory>

class Game {
    public:
        Game();
        ~Game();
        void ExecuteFrame();
        bool IsRunning();
    private:
        std::unique_ptr<Renderer2D> renderer;

};