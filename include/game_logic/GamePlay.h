#pragma once
#include "ChessBoard.h"
#include "Player.h"
#include "Enums.h"
#include "UserInterface.h"

class GamePlay {
    public:
        GamePlay(Player* white, Player* black, ChessBoard* board, UserInterface* interface);
        void takeTurn();
        bool isGameOver() const {
            return gameOver;
        }

    private:
        ChessBoard* chessBoard;
        Player* whitePlayer;
        Player* blackPlayer;
        UserInterface* userInterface;

        Color colorTurn = White;
        bool gameOver = false;

        void updateGameState();
        void updateView();
};