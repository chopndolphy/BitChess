#pragma once
#include "game_logic/ChessPiece.h"

class King : public ChessPiece {
    public:
        King(Color color, Coord location, ChessBoard* board);
        bool isLegalMove(Coord destination);
    private:
};