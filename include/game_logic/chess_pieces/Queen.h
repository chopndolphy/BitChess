#pragma once
#include "ChessPiece.h"

class Queen : public ChessPiece {
    public:
        Queen(Location square, Color pieceColor, ChessBoard* board);
        bool isLegalMove(Location square);
        char getCharacter() const  { return 'Q'; }
    private:
};