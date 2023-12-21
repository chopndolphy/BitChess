#pragma once
#include "game_logic/ChessPiece.h"

class Queen : public ChessPiece {
    public:
        Queen(Color color, Coord location, ChessBoard* board);
        bool isLegalMove(Coord destination);
    private:
        void createView();
};