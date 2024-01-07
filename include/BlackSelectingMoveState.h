#pragma once
#include "GameState.h"

class Game;

class BlackSelectingMoveState : public GameState {
    public:
        void Enter(Game &game);
        void ProcessClicks(Game &game);
        void Exit(Game &game);
        static GameState& GetInstance();
    private:
        BlackSelectingMoveState() {};
        BlackSelectingMoveState(const BlackSelectingMoveState& rs);
        BlackSelectingMoveState& operator=(const BlackSelectingMoveState rs);
};
