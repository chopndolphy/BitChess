#pragma once
#include "GameState.h"

class Game;

class WhiteSelectingMoveState : public GameState {
    public:
        void Enter(Game &game) const;
        void ProcessClicks(Game &game) const;
        void Exit(Game &game) const;
        static GameState& GetInstance();
    private:
        WhiteSelectingMoveState() {};
        WhiteSelectingMoveState(const WhiteSelectingMoveState& rs);
        WhiteSelectingMoveState& operator=(const WhiteSelectingMoveState rs);
};