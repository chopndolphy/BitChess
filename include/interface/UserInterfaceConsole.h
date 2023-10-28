#pragma once
#include "interface/UserInterface.h"

class UserInterfaceConsole : public UserInterface {
    public:
        ChessPiece* getMoveChessPiece(const Player* player, ChessBoard* board);
        std::vector<int> getMoveSquare(ChessBoard* board);
        void displayError(std::string message);
        void displayGameOver(GameState gameState);
};