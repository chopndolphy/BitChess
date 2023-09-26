#pragma once
#include "UserInterface.h"

class UserInterfaceConsole : public UserInterface {
    public:
        ChessPiece* getMoveChessPiece(const Player* player, ChessBoard* board);
        std::vector<int> getMoveSquare(ChessBoard* board);
        void displayError(std::string message);
};