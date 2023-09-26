#pragma once
#include "ChessPiece.h"

class Rook : public ChessPiece {
    public:
        Rook(std::vector<int> square, Color pieceColor, ChessBoard* board);
        bool isLegalMove(std::vector<int> square);
    private:
};