#pragma once
#include "GameState.h"

class Game;

class WhiteSelectingPieceState : public GameState {
    public:
        void Enter(Game &game) const;
        void ProcessClicks(Game &game) const;
        void Exit(Game &game) const;
        static GameState& GetInstance();
    private:
        WhiteSelectingPieceState() {};
        WhiteSelectingPieceState(const WhiteSelectingPieceState& rs);
        WhiteSelectingPieceState& operator=(const WhiteSelectingPieceState rs);
};