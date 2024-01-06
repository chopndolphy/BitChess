#pragma once
#include "GameState.h"

class Game;

class BlackSelectingPieceState : public GameState {
    public:
        void Enter(Game &game) const;
        void ProcessClicks(Game &game) const;
        void Exit(Game &game) const;
        static GameState& GetInstance();
    private:
        BlackSelectingPieceState() {};
        BlackSelectingPieceState(const BlackSelectingPieceState& rs);
        BlackSelectingPieceState& operator=(const BlackSelectingPieceState rs);
};