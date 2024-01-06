#pragma once
#include <memory>
#include <mutex>

class Game;

class GameState {
    public:
        virtual void Enter(Game &game) const = 0;
        virtual void ProcessClicks(Game &game) const = 0;
        virtual void Exit(Game &game) const = 0; 
        virtual ~GameState() {}
    private:
};