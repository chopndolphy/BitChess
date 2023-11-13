#pragma once
#include "interface/UserInterface.h"

class UserInterfaceConsole : public UserInterface {
    public:
        std::string getMove(Color color);
        ChessPiece* getMoveChessPiece(const Player* player, ChessBoard* board);
        std::vector<int> getMoveSquare();
        void displayError(std::string message);
        void displayGameOver(GameState gameState);
        void displayBoard(std::array<std::array<std::string, 8>, 8> boardView);
};