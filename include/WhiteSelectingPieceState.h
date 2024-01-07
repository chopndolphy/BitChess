#pragma once
#include "GameState.h"

class Game;

class WhiteSelectingPieceState : public GameState {
    public:
        void Enter(Game &game);
        void ProcessClicks(Game &game);
        void Exit(Game &game);
        static GameState& GetInstance();
    private:
        WhiteSelectingPieceState() {};
        WhiteSelectingPieceState(const WhiteSelectingPieceState& rs);
        WhiteSelectingPieceState& operator=(const WhiteSelectingPieceState rs);
};