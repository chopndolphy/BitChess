#pragma once
#include "GameState.h"

class Game;

class BlackSelectingMoveState : public GameState {
    public:
        void Enter(Game &game) const;
        void ProcessClicks(Game &game) const;
        void Exit(Game &game) const;
        static GameState& GetInstance();
    private:
        BlackSelectingMoveState() {};
        BlackSelectingMoveState(const BlackSelectingMoveState& rs);
        BlackSelectingMoveState& operator=(const BlackSelectingMoveState rs);
};
