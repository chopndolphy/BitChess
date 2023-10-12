#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "forward.h"
#include "alias.h"
#include "Enums.h"

class UserInterface {
    public:
    virtual ChessPiece* getMoveChessPiece(const Player* player, ChessBoard* board) = 0;
    virtual Location getMoveSquare(ChessBoard* board) = 0;
    virtual void displayError(std::string message) = 0;
    virtual void displayGameOver(GameState gameState) = 0;
};