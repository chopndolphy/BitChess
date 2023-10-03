#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "ChessPiece.h"
#include "Player.h"
#include "ChessBoard.h"

class UserInterface {
    public:
    virtual ChessPiece* getMoveChessPiece(const Player* player, ChessBoard* board) = 0;
    virtual std::vector<int> getMoveSquare(ChessBoard* board) = 0;
    virtual void displayError(std::string message) = 0;
    virtual void displayGameOver(GameState gameState) = 0;
};