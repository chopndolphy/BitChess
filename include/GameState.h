#pragma once
#include <memory>
#include <iostream>

class Game;

class GameState {
    public:
        virtual void Enter(Game &game) = 0;
        virtual void ProcessClicks(Game &game) = 0;
        virtual void Exit(Game &game) = 0; 
        virtual ~GameState() {}
    private:
};