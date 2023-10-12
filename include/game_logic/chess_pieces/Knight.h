#pragma once
#include "ChessPiece.h"

class Knight : public ChessPiece {
    public:
        Knight(Location square, Color pieceColor, ChessBoard* board);
        bool isLegalMove(Location square);
    private:
};