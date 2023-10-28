#pragma once
#include "app_logic/Enums.h"

class UserInterface;
class Player;
class ChessBoard;
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