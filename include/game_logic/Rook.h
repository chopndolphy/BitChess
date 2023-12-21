#pragma once
#include "game_logic/ChessPiece.h"

class Rook : public ChessPiece {
    public:
        Rook(Color color, Coord location, ChessBoard* board);
        bool isLegalMove(Coord destination);
    private:
        void createView();
};