#pragma once
#include "ChessPiece.h"

class Rook : public ChessPiece {
    public:
        Rook(Location square, Color pieceColor, ChessBoard* board);
        bool isLegalMove(Location square);
        char getCharacter() const  { return 'R'; }
    private:
};