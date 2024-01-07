#pragma once
#include "GameState.h"

class Game;

class WhiteSelectingMoveState : public GameState {
    public:
        void Enter(Game &game);
        void ProcessClicks(Game &game);
        void Exit(Game &game);
        static GameState& GetInstance();
    private:
        WhiteSelectingMoveState() {};
        WhiteSelectingMoveState(const WhiteSelectingMoveState& rs);
        WhiteSelectingMoveState& operator=(const WhiteSelectingMoveState rs);
};