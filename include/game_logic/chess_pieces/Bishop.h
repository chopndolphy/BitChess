#pragma once
#include "ChessPiece.h"

class Bishop : public ChessPiece {
    public:
        Bishop(Location square, Color pieceColor, ChessBoard* board);
        bool isLegalMove(Location square);
        char getCharacter() const { return 'B'; }
    private:
};