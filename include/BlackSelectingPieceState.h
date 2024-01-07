#pragma once
#include "GameState.h"

class Game;

class BlackSelectingPieceState : public GameState {
    public:
        void Enter(Game &game);
        void ProcessClicks(Game &game);
        void Exit(Game &game);
        static GameState& GetInstance();
    private:
        BlackSelectingPieceState() {};
        BlackSelectingPieceState(const BlackSelectingPieceState& rs);
        BlackSelectingPieceState& operator=(const BlackSelectingPieceState rs);
};