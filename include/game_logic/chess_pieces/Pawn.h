#pragma once
#include "ChessPiece.h"

class Pawn : public ChessPiece {
    public:
        Pawn(Location square, Color pieceColor, ChessBoard* board);
        bool isLegalMove(Location square);
    private:  
        bool canEnPassant(Location square);
};