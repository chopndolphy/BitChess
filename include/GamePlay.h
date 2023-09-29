#pragma once
#include "ChessBoard.h"
#include "Player.h"
#include "Enums.h"
#include "UserInterface.h"

class GamePlay {
    public:
        GamePlay(Player* white, Player* black, ChessBoard* board, UserInterface* interface);
        void setGameOver(Outcome outcome);
        void takeTurn();
        const bool isGameOver() const {
            return isGameOver;
        }

    private:
        ChessBoard* chessBoard;
        Player* whitePlayer;
        Player* blackPlayer;
        UserInterface* userInterface;

        Color colorTurn;
        Outcome gameOutcome;
        bool isGameOver;

};