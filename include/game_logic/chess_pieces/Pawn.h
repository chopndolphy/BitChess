#pragma once
#include "ChessPiece.h"

class Pawn : public ChessPiece {
    public:
        Pawn(Location square, Color pieceColor, ChessBoard* board);
        bool isLegalMove(Location square);
        char getCharacter() const  { return 'P'; }
};