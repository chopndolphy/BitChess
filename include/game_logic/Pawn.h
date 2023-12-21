#pragma once
#include "game_logic/ChessPiece.h"

class Pawn : public ChessPiece {
    public:
        Pawn(Color color, Coord location, ChessBoard* board);
        bool isLegalMove(Coord destination);
        void setDoubleMoved(bool hasDoubleMoved);
    private:  
        bool canEnPassant(Coord destination);
        void createView();
};