#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "ChessPiece.h"
#include "Player.h"
#include "ChessBoard.h"

class UserInterface {
    public:
    virtual ChessPiece* getMoveChessPiece(const Player* player, ChessBoard* board);
    virtual std::vector<int> getMoveSquare(ChessBoard* board);
    virtual void displayError(std::string message);
};