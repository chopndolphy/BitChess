#pragma once
#include "ChessPiece.h"

class King : public ChessPiece {
    public:
        King(Location square, Color pieceColor, ChessBoard* board);
        bool isLegalMove(Location square);
    private:
};