#pragma once
#include "game_logic/ChessPiece.h"
class Bishop : public ChessPiece {
    public:
        Bishop(std::vector<int> square, Color pieceColor, ChessBoard* board);
        bool isLegalMove(std::vector<int> square);
    private:
};