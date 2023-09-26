#pragma once
#include "Outcome.h"
#include "ChessBoard.h"
#include "Player.h"

class GamePlay {
    public:
        void setGameOver(Outcome outcome);
    private:
        ChessBoard* chessBoard;
        Player* whitePlayer;
        Player* blackPlayer;
        bool isWhitesTurn;
        bool isGameOver;
};