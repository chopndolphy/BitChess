#pragma once
#include "ChessPiece.h"

class King : public ChessPiece {
    public:
        King(std::vector<int> square, Color pieceColor, ChessBoard* board);
        bool isLegalMove(std::vector<int> square);
    private:
};