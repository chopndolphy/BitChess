#pragma once
#include "forward.h"
#include "alias.h"
#include "Enums.h"
#include "UserInterface.h"

class UserInterfaceConsole : public UserInterface {
    public:
        ChessPiece* getMoveChessPiece(const Player* player, ChessBoard* board);
        Location getMoveSquare(ChessBoard* board);
        void displayError(std::string message);
        void displayGameOver(GameState gameState);
};