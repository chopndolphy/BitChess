#pragma once
#include "ChessPiece.h"

class Knight : public ChessPiece {
    public:
        Knight(std::vector<int> square, Color pieceColor, ChessBoard* board);
        bool isLegalMove(std::vector<int> square);
    private:
};